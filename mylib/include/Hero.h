#pragma once

#include "IGameObject.h"
#include "HealthComponent.h"
#include "MovementComponent.h"
#include "StateComponent.h"

namespace HeroStateNames
{
	enum class stateName
	{
		idle,
		run,
		attack,
		block,
		dodge,
		hurt,
		death
	};
}

class Hero : public IGameObject
{
public:
    Hero(IGameObjectContainer& game, const Vec2& position);

    void takeDamage(int damage);
    bool isAlive() const;
    void move(const Vec2& direction, float deltaTime);
    Vec2 getPosition() const;
    void setState(StateComponent::StateName newState);
    StateComponent::StateName getCurrentState() const;
    void update(float deltaTime) override;
    void Hero::render(sf::RenderWindow& window) override;

private:
    HealthComponent m_healthComponent;
    MovementComponent m_movementComponent;
    StateComponent m_stateComponent;
};
