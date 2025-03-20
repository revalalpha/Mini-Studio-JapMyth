#include "Hero.h"

Hero::Hero(const std::string& name) : m_stateManager(this)
{
    m_stateManager.registerState("Idle", [this](Hero* hero) { return StateFactory::createState("Idle", this); });
    m_stateManager.registerState("Run", [this](Hero* hero) { return StateFactory::createState("Run", this); });
    m_stateManager.registerState("Attack", [this](Hero* hero) { return StateFactory::createState("Attack", this); });
    m_stateManager.registerState("Shoot", [this](Hero* hero) { return StateFactory::createState("Shoot", this); });
    m_stateManager.registerState("Hurt", [this](Hero* hero) { return StateFactory::createState("Hurt", this); });
    m_stateManager.registerState("Death", [this](Hero* hero) { return StateFactory::createState("Death", this); });

    m_stateManager.changeState("Idle");

    m_health = 100;
    m_isFacingLeft = false;
    m_currentStateName = stateName::idle;
}

Hero::~Hero() = default;

void Hero::initialize(const sf::Vector2f& position, float size, const sf::Color& color, float speed)
{
    m_position = position;
    m_speed = speed;
    m_health = 100;
    m_stateManager.changeState("Idle");
}

void Hero::update(const float& deltaTime)
{
    m_stateManager.update(deltaTime);
}

void Hero::processInput(const sf::Event& event)
{
    m_stateManager.handleInput();
}

void Hero::handleInput()
{
    sf::Vector2f direction(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        direction.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        direction.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        direction.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        direction.x += 1.f;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
        direction /= length;

    m_sprite.move(direction * m_speed);
}

bool Hero::isAlive() const
{
    return m_health > 0;
}

bool Hero::isFacingLeft() const
{
    return m_isFacingLeft;
}

void Hero::takeDamage(int amount)
{
    m_health -= amount;
    if (m_health <= 0)
    {
        setState(stateName::death);
    }
    else
    {
        setState(stateName::hurt);
    }
}

void Hero::move(const sf::Vector2f& offset)
{
    m_position += offset;
}

void Hero::setFacingLeft(bool left)
{
    m_isFacingLeft = left;
}

void Hero::setDirection(Direction dir)
{
    m_currentDirection = dir;
}

Direction Hero::getDirection() const
{
    return m_currentDirection;
}

void Hero::attack()
{
    setState(stateName::meleeAttack);
}

void Hero::shoot()
{
    setState(stateName::rangeAttack);
}

stateName Hero::getCurrentState() const
{
    return m_currentStateName;
}

void Hero::setState(stateName newState)
{
    if (m_currentStateName != newState)
    {
        switch (newState)
        {
        case stateName::idle:
            m_stateManager.changeState("Idle");
            break;
        case stateName::run:
            m_stateManager.changeState("Run");
            break;
        case stateName::meleeAttack:
            m_stateManager.changeState("Attack");
            break;
        case stateName::rangeAttack:
            m_stateManager.changeState("Shoot");
            break;
        case stateName::hurt:
            m_stateManager.changeState("Hurt");
            break;
        case stateName::death:
            m_stateManager.changeState("Death");
            break;
        }
        m_currentStateName = newState;
    }
}

sf::Sprite& Hero::getSprite()
{
    return m_sprite;
}

StateManager& Hero::getStateManager()
{
    return m_stateManager;
}

void Hero::addComponent(std::shared_ptr<Composite> component)
{
    if (component) 
    {
        m_components[component->getName()] = component;
        component->setOwner(this);
    }
}

void Hero::removeComponent(const std::string& name)
{
    m_components.erase(name);
}

Composite* Hero::getComponent(const std::string& name)
{
    return m_components.find(name) != m_components.end() ? m_components[name].get() : nullptr;
}

const Composite* Hero::getComponent(const std::string& name) const
{
    auto it = m_components.find(name);
    return (it != m_components.end()) ? it->second.get() : nullptr;
}

float Hero::getSpeed() const
{
    return m_speed;
}

const sf::Vector2f& Hero::getPosition() const
{
    return m_position;
}

bool Hero::isGoingLeft() const
{
	return m_movingLeft;
}

bool Hero::isGoingRight() const
{
	return m_movingRight;
}

bool Hero::isGoingUp() const
{
	return m_movingUp;
}

bool Hero::isGoingDown() const
{
	return m_movingDown;
}

void Hero::updateDirection()
{
}

bool Hero::isAttacking() const
{
	return m_attacking;
}

bool Hero::isShooting() const
{
	return m_shooting;
}
