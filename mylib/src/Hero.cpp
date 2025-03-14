#include "Hero.h"

Hero::Hero(IGameObjectContainer& game, const Vec2& position)
    : IGameObject(game),
    m_healthComponent(100),
    m_movementComponent(70.f),
    m_stateComponent()
{
    m_movementComponent.move(position, 0.0f);
}

void Hero::takeDamage(int damage)
{
    m_healthComponent.takeDamage(damage);
}

bool Hero::isAlive() const
{
    return m_healthComponent.isAlive();
}

void Hero::move(const Vec2& direction, float deltaTime)
{
    m_movementComponent.move(direction, deltaTime);
}

Vec2 Hero::getPosition() const
{
    return m_movementComponent.getPosition();
}

void Hero::setState(StateComponent::StateName newState)
{
    m_stateComponent.setState(newState);
}

StateComponent::StateName Hero::getCurrentState() const
{
    return m_stateComponent.getCurrentState();
}

void Hero::update(float deltaTime)
{
    m_healthComponent.update(deltaTime);
    m_movementComponent.update(deltaTime);
    m_stateComponent.update(deltaTime);
}

void Hero::render(sf::RenderWindow& window)
{
    //Sprite
}
