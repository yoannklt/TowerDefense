#include "Collisions.h"
#include "../objects/GameObject.h"
#include "../objects/MovingObject.h"
#include <iostream>
#include <SFML/System/Vector2.hpp>
#include "../utils/Maths.h"

void Collisions::registerStaticBody(GameObject* staticBody) {
	this->staticBodies.push_back(staticBody);
}

void Collisions::registerRigidBody(MovingObject* rigidBody) {
	this->rigidBodies.push_back(rigidBody);
}

void Collisions::unregisterStaticBody(GameObject* staticBody)
{
	this->staticBodies.erase(std::remove(this->staticBodies.begin(), this->staticBodies.end(), staticBody), this->staticBodies.end());
}

void Collisions::unregisterRigidBody(MovingObject* rigidBody)
{
	this->rigidBodies.erase(std::remove(this->rigidBodies.begin(), this->rigidBodies.end(), rigidBody), this->rigidBodies.end());
}

CollisionData* Collisions::checkAABBCollision(MovingObject* movingObject, GameObject* staticObject)
{
	// checks if there is no collision and then takes the inverse as condition
	if (!(movingObject->getXMax() < staticObject->getX() || movingObject->getX() > staticObject->getXMax()
		||
		movingObject->getYMax() < staticObject->getY() || movingObject->getY() > staticObject->getYMax())) {

		float movingOrientationX = movingObject->getOrientation().x;
		float movingOrientationY = movingObject->getOrientation().y;

		//check if it was a vertical or horizontal collision first
		float movingX = movingObject->getX() * (movingOrientationX < 0) + movingObject->getXMax() * (movingOrientationX > 0);
		float movingY = movingObject->getY() * (movingOrientationY < 0) + movingObject->getYMax() * (movingOrientationY > 0);

		float staticX = staticObject->getX() * (movingOrientationX > 0) + staticObject->getXMax() * (movingOrientationX < 0);
		float staticY = staticObject->getY() * (movingOrientationY > 0) + staticObject->getYMax() * (movingOrientationY < 0);

		float moveCoefficient = (movingX - staticX) / movingOrientationX; //moveCoefficient is equivalent to speed * dt in new pos calculation (MovingObject)
		float newPosY = movingOrientationY * moveCoefficient + staticY;
		if (
			((newPosY > movingY) && (movingOrientationY < 0))
			||
			((newPosY < movingY) && (movingOrientationY > 0))
			) {
			//vertical collision
			return new CollisionData{ sf::Vector2f(0.f, 1.f), moveCoefficient };
		}
		else {
			//horizontal collision
			return new CollisionData{ sf::Vector2f(1.f, 0.f), (movingY - staticY) / movingOrientationY };
		}
	}
	return new CollisionData{ sf::Vector2f(0.f, 0.f), 20000.f }; // second value should be replaced with the physical step + 1 (so that it's an impossible step)
}

/*CollisionData Collisions::checkAABBCollisionWithPhysicalStep(MovingObject* movingObject, GameObject* staticObject)
{

	if( (movingObject->getXMax() < staticObject->getX() || movingObject->getX() > staticObject-> getXMax()
		||
		movingObject->getYMax() < staticObject->getY() || movingObject->getY() > staticObject->getYMax())
	) {

		float deltaMove = movingObject->getSpeed() * GameManager::deltaTime;

		float movingOrientationX = movingObject->getOrientation().x;
		float movingOrientationY = movingObject->getOrientation().y;

		float oppositOrientationX = -movingOrientationX;
		float oppositOrientationY = -movingOrientationY;

		//shared means the X/Y value present on two of the 3 necessary vertexes.
		float movingSharedX = movingObject->getX() * (movingOrientationX < 0) + movingObject->getXMax() * (movingOrientationX > 0);
		float movingSharedY = movingObject->getY() * (movingOrientationY < 0) + movingObject->getYMax() * (movingOrientationY > 0);

		float movingUnsharedX = movingObject->getX() * (movingOrientationX > 0) + movingObject->getXMax() * (movingOrientationX < 0);
		float movingUnsharedY = movingObject->getY() * (movingOrientationY > 0) + movingObject->getYMax() * (movingOrientationY < 0);

		sf::Vector2f movingVertexesList[3] = {
			sf::Vector2f{ movingSharedX, movingUnsharedY },
			sf::Vector2f{ movingSharedX, movingSharedY },
			sf::Vector2f{ movingUnsharedX, movingSharedY }
		};

		float deltaMoveX = movingOrientationX * deltaMove;
		float deltaMoveY = movingOrientationY * deltaMove;

		sf::Vector2f previousPositionMovingVertexesList[3] = {
			sf::Vector2f{ movingSharedX - deltaMoveX, movingUnsharedY - deltaMoveY },
			sf::Vector2f{ movingSharedX - deltaMoveX, movingSharedY - deltaMoveY },
			sf::Vector2f{ movingUnsharedX - deltaMoveX, movingSharedY - deltaMoveY }
		};

		float staticY[2] = { staticObject->getY(), staticObject->getYMax() };
		bool staticYIndex = movingOrientationY > 0;
		sf::Vector2f staticVertexA = sf::Vector2f{ staticObject->getX(), staticY[staticYIndex] };
		sf::Vector2f staticVertexB = sf::Vector2f{ staticObject->getXMax(), staticY[!staticYIndex] };


		for (int i = 0; i < 3; i++) {
			intersection = getIntersectionBetweenSegments(previousPositionMovingVertexesList[i], movingVertexesList[i], staticVertexA, staticVertexB)
		}

		//compare intersections between each others to see which one is the farthest and should be used as collision point

	} else {
		checkAABBCollision(movingObject, staticObject)
	}


	float movingOrientationX = movingObject->getOrientation().x;
	float movingOrientationY = movingObject->getOrientation().y;

	float movingX = movingObject->getX() * (movingOrientationX < 0) + movingObject->getXMax() * (movingOrientationX > 0);
	float movingY = movingObject->getY() * (movingOrientationY < 0) + movingObject->getYMax() * (movingOrientationY > 0);

	float staticX = staticObject->getX() * (movingOrientationX > 0) + staticObject->getXMax() * (movingOrientationX < 0);
	float staticY = staticObject->getY() * (movingOrientationY > 0) + staticObject->getYMax() * (movingOrientationY < 0);

	sf::Vector2f intersection = Maths::getIntersectionBetweenSegments(sf::Vector2f{ movingX, movingY }, sf::Vector2f vertexB, sf::Vector2f vertexC, sf::Vector2f vertexD)

}*/

void Collisions::checkCollisions()
{
	for (int i = 0; i < this->rigidBodies.size(); ++i) {
		MovingObject* rigidBody = rigidBodies[i];
		for (int j = 0; j < this->staticBodies.size(); ++j) {
			GameObject* staticBody = staticBodies[j];
			CollisionData* collisionData = checkAABBCollision(rigidBody, staticBody);
			if (collisionData->overMoveCoefficient != 20000) { //means no colisions were detected
				for (int k = 0; k < collisionsList.size(); ++k) {
					if ((collisionData->collisionSide.x != collisionsList[k]->collisionSide.x) && (collisionData->collisionSide.y != collisionsList[k]->collisionSide.y) && (collisionData->overMoveCoefficient != collisionsList[k]->overMoveCoefficient)) {
						collisionsList.push_back(collisionData);
					}
				}
				if (collisionsList.size() == 0) {
					collisionsList.push_back(collisionData);
				}
				staticBody->onCollision(collisionData->collisionSide);
			}
		}
		for (CollisionData* collisionData : this->collisionsList) {
			rigidBody->onCollision(collisionData->collisionSide); //triggerEvent on Specific
			rigidBody->setPosition( //fixing the moving object position out of the object it collided with
				collisionData->overMoveCoefficient * rigidBody->getOrientation().x + rigidBody->getPosition().x,
				collisionData->overMoveCoefficient * rigidBody->getOrientation().y + rigidBody->getPosition().y
			);
			//delete collisionData;

		}
		this->collisionsList.clear();
	}
}





/*
// checks if there is a collision
bool longestWidthIndex = movingObject->getWidth() < gameObject->getWidth();
bool longestHeightIndex = movingObject->getHeight() < gameObject->getHeight();

GameObject* longWidthObject = longestWidthIndex ? gameObject : movingObject;
GameObject* longHeightObject = longestHeightIndex ? gameObject : movingObject;
GameObject* shortWidthObject = !longestWidthIndex ? gameObject : movingObject;
GameObject* shortHeightObject = !longestHeightIndex ? gameObject : movingObject;



if ((longWidthObject->getX() < shortWidthObject->getX() && shortWidthObject->getX() < longWidthObject->getXMax()
	||
	(longWidthObject->getX() < shortWidthObject->getXMax() && shortWidthObject->getXMax() < longWidthObject->getXMax()))
	&&
	((longHeightObject->getX() < shortHeightObject->getX() && shortHeightObject->getX() < longHeightObject->getXMax())
		||
		(longHeightObject->getX() < shortHeightObject->getXMax() && shortHeightObject->getXMax() < longHeightObject->getXMax())))
{ */



/*


sf::Vector2f getAssociatedVector(vertexList[i] v1, vertexList[i+1] v2){
	return {v2.x - v1.x, v2.y - v1.y}
};


sf::Vector2f areIntersecting(sf::Vector2f segment1[2], sf::Vector2f segment2[2]) {
	directionalVector1 = getAssociatedVector(segment1[0], segment1[1]);
	directionalVector2 = getAssociatedVector(segment2[0], segment2[1]);
	sf::Vector2f point = getIntersectionPointBetweenRights(directionalVector1, directionalVector2);
	if()

}


class Collider {
private:
std::vector<sf::Vector2f> vertexList;
}
*/


/*

//check if the two segments are intersecting

	float numerator = (pointA.x - pointC.x)*(pointC.y - pointD.y)-(pointA.y - pointC.y)*(pointC.x - pointD.x);
	float denominator = (pointA.x - pointB.x)*(pointC.y - pointD.y)-(pointA.y - pointB.y)*(pointC.x - pointD.x);
	float t = numerator/denominator;

	Point intersection;
	constructPoint(&intersection, pointA.x + t*(pointB.x - pointA.x), pointA.y + t*(pointB.y - pointA.y));

*/