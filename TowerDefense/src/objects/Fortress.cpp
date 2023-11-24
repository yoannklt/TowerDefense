#include "Fortress.h"
#include <SFML/Graphics/Sprite.hpp>
#include "../engine/textures/TextureManager.h"
#include "../engine/core/GameManager.h"
#include "../engine/core/GameState.h"
#include "../engine/events/MethodCommand.h"

Fortress::Fortress(float x, float y, float width, float height, Text* text) : GameObject(x, y, width, height)//, healthText("Health:", { x, y+10 }, "data/assets/graphics/fonts/Roboto-Regular.ttf", 40, sf::Color::White)
{
	GameManager::instance().getEventsManager()->subscribe(ENEMY_ATTACKED, new MethodCommand<Fortress>(this, &Fortress::onDamaged));
	this->healthText = text;
	this->healthText->updateText("Health: " + std::to_string(this->health));
	this->sprite = new sf::Sprite(*TextureManager::getTexture("fortress.png"));
	this->drawable = this->sprite;
	this->transformable = this->sprite;
	this->sprite->setPosition(x, y);
	this->sprite->setScale(this->size.x / this->sprite->getGlobalBounds().width, this->size.y / this->sprite->getGlobalBounds().height);
	this->sprite->setOrigin(width, height);

}

Fortress::~Fortress()
{
}

void Fortress::update(float deltaTime)
{
}

void Fortress::onDamaged()
{
	--this->health;
	this->healthText->updateText("Health: " + std::to_string(this->health));
	if (this->health <= 0)
	{
		GameManager::instance().getEventsManager()->trigger(GAME_OVER_DEFEAT);
	}
}
