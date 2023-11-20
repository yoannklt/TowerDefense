#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <set>
#include <iostream>

class GameObject;
class MovingObject;

struct CollisionData {
	sf::Vector2f collisionSide;
	float overMoveCoefficient;

	bool operator<(const CollisionData& other) {
		std::cout << "called";
		if (collisionSide.x != other.collisionSide.x) { std::cout << "different"; return collisionSide.x < other.collisionSide.x; }
		if (collisionSide.y != other.collisionSide.y) { std::cout << "different";  return collisionSide.y < other.collisionSide.y; }
		std::cout << "different";
		return overMoveCoefficient < other.overMoveCoefficient;
	}
};

class Collisions
{
public:
	Collisions() {};
	~Collisions() {};
	void registerStaticBody(GameObject* staticBody);
	void registerRigidBody(MovingObject* rigidBody);
	void unregisterStaticBody(GameObject* staticBody);
	void unregisterRigidBody(MovingObject* rigidBody);
	void checkCollisions();
	CollisionData* checkAABBCollision(MovingObject* movingObject, GameObject* gameObject);
	CollisionData checkAABBCollisionWithPhysicalStep(MovingObject* movingObject, GameObject* staticObject);
	CollisionData checkOBBCollision(MovingObject* movingObject, GameObject* staticObject);
private:
	std::vector<GameObject*> staticBodies;
	std::vector<MovingObject*> rigidBodies;
	std::vector<CollisionData*> collisionsList;
};