#include "HeroState.h"
#include <SFML/Graphics.hpp>
#include <iostream>

HeroState::HeroState(Hero* owner) : m_owner(owner), m_currentState(nullptr)
{
    initialize();
}

HeroState::~HeroState()
{}

void HeroState::initialize()
{
    m_states.insert(std::make_pair("Idle", std::make_unique<IdleState>(m_owner)));
    m_states.insert(std::make_pair("Run", std::make_unique<RunState>(m_owner)));
    m_states.insert(std::make_pair("Attack", std::make_unique<AttackState>(m_owner)));
    m_states.insert(std::make_pair("Shoot", std::make_unique<ShootState>(m_owner)));
    m_states.insert(std::make_pair("Hurt", std::make_unique<HurtState>(m_owner)));
    m_states.insert(std::make_pair("Death", std::make_unique<DeathState>(m_owner)));

    changeState("Idle");
}

void HeroState::update(float deltaTime)
{
    if (m_currentState)
        m_currentState->update(*m_owner, deltaTime);
}

void HeroState::handleInput()
{
    if (m_currentState)
        m_currentState->handleInput(*m_owner);
}

void HeroState::changeState(const std::string& stateName)
{
    auto it = m_states.find(stateName);
    if (it == m_states.end())
    {
        std::cerr << "State " << stateName << " does not exist!" << std::endl;
        return;
    }

    if (m_currentState)
        m_currentState->exit(*m_owner);

    m_currentStateName = stateName;
    m_currentState = it->second.get();

    if (m_currentState)
        m_currentState->enter(*m_owner);
}

std::string HeroState::getCurrentStateName() const
{
    return m_currentStateName;
}

void IdleState::enter(Hero& owner)
{
    owner.setState(stateName::idle);
}

void IdleState::handleInput(Hero& owner)
{
    if (owner.isGoingLeft() || owner.isGoingRight() ||
        owner.isGoingUp() || owner.isGoingDown())
        owner.getStateManager().changeState("Run");

    if (owner.isAttacking())
        owner.getStateManager().changeState("Attack");

    if (owner.isShooting())
        owner.getStateManager().changeState("Shoot");
}

void RunState::enter(Hero& owner)
{
    owner.setState(stateName::run);
}

void RunState::handleInput(Hero& owner)
{
    if (!owner.isGoingLeft() && !owner.isGoingRight() &&
        !owner.isGoingUp() && !owner.isGoingDown())
    {
        owner.getStateManager().changeState("Idle");
        return;
    }

    sf::Vector2f moveOffset(0.0f, 0.0f);

    if (owner.isGoingLeft())
    {
        owner.setDirection(Direction::Left);
        owner.setFacingLeft(true);
        moveOffset.x -= owner.getSpeed();
    }
    if (owner.isGoingRight())
    {
        owner.setDirection(Direction::Right);
        owner.setFacingLeft(false);
        moveOffset.x += owner.getSpeed();
    }
    if (owner.isGoingUp())
    {
        owner.setDirection(Direction::Up);
        moveOffset.y -= owner.getSpeed();
    }
    if (owner.isGoingDown())
    {
        owner.setDirection(Direction::Down);
        moveOffset.y += owner.getSpeed();
    }

    owner.move(moveOffset);

    // Check for attack input
    if (owner.isAttacking())
        owner.getStateManager().changeState("Attack");

    if (owner.isShooting())
        owner.getStateManager().changeState("Shoot");
}

void RunState::update(Hero& owner, float deltaTime)
{
    owner.updateDirection();
}

void AttackState::enter(Hero& owner)
{
    owner.setState(stateName::meleeAttack);
    m_animClock.restart();
    owner.attack();
}

void AttackState::update(Hero& owner, float deltaTime)
{
    const float attackDuration = 0.6f;

    if (m_animClock.getElapsedTime().asSeconds() >= attackDuration)
        owner.getStateManager().changeState("Idle");
}

// ShootState implementation
void ShootState::enter(Hero& owner)
{
    owner.setState(stateName::rangeAttack);
    m_animClock.restart();

    owner.shoot();
}

void ShootState::update(Hero& owner, float deltaTime)
{
    const float shootDuration = 0.4f;

    if (m_animClock.getElapsedTime().asSeconds() >= shootDuration)
        owner.getStateManager().changeState("Idle");
}

void HurtState::enter(Hero& owner)
{
    owner.setState(stateName::hurt);
    m_animClock.restart();
}

void HurtState::update(Hero& owner, float deltaTime)
{
    if (m_animClock.getElapsedTime().asSeconds() >= m_hurtDuration)
    {
        if (!owner.isAlive())
            owner.getStateManager().changeState("Death");
        else
            owner.getStateManager().changeState("Idle");
    }
}

void DeathState::enter(Hero& owner)
{
    owner.setState(stateName::death);
}