#include "ennemie.h"

IEnnemies::IEnnemies(Game* game, int health)
    : m_game(game), m_currentTarget(nullptr), m_health(health),
    m_isInvulnerable(false), m_invulnerableDuration(0.f),
    m_currentState(State::Idle), m_rootNode(this)
{}

void IEnnemies::update(float deltaTime)
{
    if (m_health <= 0)
        return;

    if (m_animations.find(m_currentState) != m_animations.end()) 
    {
        // Anim
    }

	m_rootNode.tick();
}

void IEnnemies::takeDamage(int damage)
{
    if (!m_isInvulnerable) 
    {
        m_health -= damage;
        if (m_health <= 0)
            setState(State::Hurt);
    }
}

void IEnnemies::attack()
{
    setState(State::Attack1);
}

bool IEnnemies::isAlive()
{
    return m_health > 0;
}

bool IEnnemies::isInvulnerable()
{
    return m_isInvulnerable;
}

void IEnnemies::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}

void IEnnemies::setState(State newState)
{
    m_currentState = newState;
}

IEnnemies::State IEnnemies::getState() const
{
    return m_currentState;
}
