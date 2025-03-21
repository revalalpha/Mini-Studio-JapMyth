//#include "Hero.h"
//#include "TextureManager.h"
//#include "Animation.h"
//
//Hero::Hero(const std::string& name) :
//    ComponentGameObject(name),
//    m_stateManager(this),
//    m_health(100),
//    m_armor(0),
//    m_strength(10),
//    m_speed(200.0f),
//    m_currentStateName(stateName::idle),
//    m_currentDirection(Direction::Down),
//    m_isFacingLeft(false),
//    m_knockBackDuration(0.0f)
//{
//    setCategory("Player");
//    addTag("Hero");
//}
//
//Hero::~Hero() = default;
//
//void Hero::initialize(const sf::Vector2f& position, float size, const sf::Color& color, float speed)
//{
//    m_speed = speed;
//
//    auto renderer = std::make_shared<SquareRenderer>(size, color);
//    this->addComponent(renderer);
//    renderer->setPosition(position);
//
//    auto controller = std::make_shared<PlayerController>(speed);
//    addComponent(controller);
//
//    auto animComp = std::make_shared<AnimationComponent>();
//    addComponent(animComp);
//
//    auto hitbox = std::make_shared<Hitbox>(sf::Vector2f(60.f, 60.f));
//    hitbox->setDebugDraw(true);
//    addComponent(hitbox);
//}
//
//void Hero::update(const float& deltaTime)
//{
//    if (m_knockBackDuration > 0)
//    {
//        m_knockBackDuration -= deltaTime;
//
//        auto renderer = static_cast<SquareRenderer*>(getComponent("SquareRenderer"));
//        if (renderer)
//        {
//            sf::Vector2f currentPos = renderer->getPosition();
//
//            float slowdownFactor = std::min(1.0f, 4.0f * deltaTime);
//            m_knockBack *= (1.0f - slowdownFactor);
//
//            renderer->setPosition(currentPos + m_knockBack * deltaTime);
//            /*m_position = currentPos + m_knockBack * deltaTime;*/
//        }
//    }
//
//    ComponentGameObject::update(deltaTime);
//    /*updateComponents(deltaTime);*/
//    m_stateManager.update(deltaTime);
//    updateAnimationPosition();
//}
//
//void Hero::updateComponents(const float& deltaTime)
//{
//    for (auto& [name, component] : m_components)
//    {
//        if (component)
//            component->update(deltaTime);
//    }
//}
//
//void Hero::updateAnimationPosition()
//{
//    auto renderer = static_cast<SquareRenderer*>(getComponent("SquareRenderer"));
//    auto animComp = static_cast<AnimationComponent*>(getComponent("AnimationComponent"));
//
//    if (renderer && animComp)
//    {
//        sf::Vector2f position = renderer->getPosition();
//        animComp->updatePosition(position);
//        m_position = position;
//    }
//}
//
//void Hero::processInput(const sf::Event& event)
//{
//    ComponentGameObject::processInput(event);
//
//    m_stateManager.handleInput();
//}
//
//void Hero::handleInput()
//{
//    sf::Vector2f direction(0.f, 0.f);
//
//    m_movingUp = false;
//    m_movingDown = false;
//    m_movingLeft = false;
//    m_movingRight = false;
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
//    {
//        direction.y -= 1.f;
//        m_movingUp = true;
//        setDirection(Direction::Up);
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//    {
//        direction.y += 1.f;
//        m_movingDown = true;
//        setDirection(Direction::Down);
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
//    {
//        direction.x -= 1.f;
//        m_movingLeft = true;
//        setDirection(Direction::Left);
//        setFacingLeft(true);
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
//    {
//        direction.x += 1.f;
//        m_movingRight = true;
//        setDirection(Direction::Right);
//        setFacingLeft(false);
//    }
//
//    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
//    if (length != 0)
//        direction /= length;
//
//    if (length != 0 && m_currentStateName != stateName::meleeAttack &&
//        m_currentStateName != stateName::rangeAttack && m_currentStateName != stateName::hurt)
//        setState(stateName::run);
//    else if (length == 0 && m_currentStateName == stateName::run)
//        setState(stateName::idle);
//
//    m_sprite.move(direction * m_speed);
//
//    auto renderer = static_cast<SquareRenderer*>(getComponent("SquareRenderer"));
//    if (renderer)
//    {
//        renderer->setPosition(m_sprite.getPosition());
//        m_position = m_sprite.getPosition();
//    }
//}
//
//void Hero::handleInputs(const sf::Event& event)
//{
//    handleInput();
//}
//
//void Hero::render(sf::RenderWindow& window)
//{
//    for (auto& [name, component] : m_components)
//    {
//        if (component)
//            component->render(window);
//    }
//
//    window.draw(m_sprite);
//}
//
//bool Hero::isAlive() const
//{
//    return m_health > 0;
//}
//
//bool Hero::isFacingLeft() const
//{
//    return m_isFacingLeft;
//}
//
//void Hero::takeDamage(int amount)
//{
//    int actualDamage = amount - m_armor;
//    if (actualDamage < 1)
//        actualDamage = 1;
//
//    m_health -= actualDamage;
//
//    if (m_health <= 0)
//    {
//        m_health = 0;
//        setState(stateName::death);
//    }
//    else
//    {
//        setState(stateName::hurt);
//    }
//}
//
//void Hero::move(const sf::Vector2f& offset)
//{
//    m_position += offset;
//
//    auto renderer = static_cast<SquareRenderer*>(getComponent("SquareRenderer"));
//    if (renderer)
//    {
//        sf::Vector2f currentPos = renderer->getPosition();
//        renderer->setPosition(currentPos + offset);
//    }
//
//    m_sprite.move(offset);
//}
//
//void Hero::setFacingLeft(bool left)
//{
//    m_isFacingLeft = left;
//
//    if (left)
//        m_currentDirection = Direction::Left;
//    else
//        m_currentDirection = Direction::Right;
//
//    auto animComp = static_cast<AnimationComponent*>(getComponent("AnimationComponent"));
//    if (animComp)
//    {
//        if (m_isFacingLeft && (m_currentDirection == Direction::Left || m_currentDirection == Direction::Right))
//            animComp->setScale(sf::Vector2f(-2.0f, 2.0f));
//        else
//            animComp->setScale(sf::Vector2f(2.0f, 2.0f));
//    }
//}
//
//void Hero::setDirection(Direction dir)
//{
//    m_currentDirection = dir;
//
//    if (dir == Direction::Left)
//        m_isFacingLeft = true;
//    else if (dir == Direction::Right)
//        m_isFacingLeft = false;
//}
//
//Direction Hero::getDirection() const
//{
//    return m_currentDirection;
//}
//
//void Hero::attack()
//{
//     m_stateManager.changeState("Attack");
//}
//
//void Hero::shoot()
//{
//    m_shooting = true;
//    setState(stateName::rangeAttack);
//}
//
//stateName Hero::getCurrentState() const
//{
//    return m_currentStateName;
//}
//
//void Hero::setState(stateName newState)
//{
//    if (m_currentStateName != newState)
//    {
//        switch (newState)
//        {
//        case stateName::idle:
//            m_stateManager.changeState("Idle");
//            break;
//        case stateName::run:
//            m_stateManager.changeState("Run");
//            break;
//        case stateName::meleeAttack:
//            m_stateManager.changeState("Attack");
//            break;
//        case stateName::rangeAttack:
//            m_stateManager.changeState("Shoot");
//            break;
//        case stateName::hurt:
//            m_stateManager.changeState("Hurt");
//            break;
//        case stateName::death:
//            m_stateManager.changeState("Death");
//            break;
//        }
//
//        m_currentStateName = newState;
//
//        updateAnimation(newState);
//    }
//}
//
//void Hero::updateAnimation(stateName newState)
//{
//    auto animComp = static_cast<AnimationComponent*>(getComponent("AnimationComponent"));
//    if (!animComp)
//        return;
//
//    std::string directionSuffix;
//    switch (m_currentDirection)
//    {
//    case Direction::Up:
//        directionSuffix = "_up";
//        break;
//    case Direction::Down:
//        directionSuffix = "_down";
//        break;
//    case Direction::Right:
//    case Direction::Left:
//        directionSuffix = "_right";
//        break;
//    }
//
//    if (newState == stateName::hurt)
//    {
//        animComp->playAnimation("hurt");
//        return;
//    }
//
//    if (newState == stateName::death)
//    {
//        animComp->playAnimation("death");
//        return;
//    }
//
//    switch (newState)
//    {
//    case stateName::idle:
//        animComp->playAnimation("idle" + directionSuffix);
//        break;
//    case stateName::run:
//        animComp->playAnimation("run" + directionSuffix);
//        break;
//    case stateName::meleeAttack:
//        animComp->playAnimation("attack" + directionSuffix);
//        break;
//    case stateName::rangeAttack:
//        animComp->playAnimation("shoot" + directionSuffix);
//        break;
//    default:
//        break;
//    }
//
//    if (m_isFacingLeft && (m_currentDirection == Direction::Left || m_currentDirection == Direction::Right))
//        animComp->setScale(sf::Vector2f(-2.0f, 2.0f));
//    else
//        animComp->setScale(sf::Vector2f(2.0f, 2.0f));
//}
//
//sf::Sprite& Hero::getSprite()
//{
//    return m_sprite;
//}
//
//sf::Vector2f Hero::getPosition()
//{
//    return m_position;
//}
//
//HeroState& Hero::getStateManager()
//{
//    return m_stateManager;
//}
//
//void Hero::addComponent(std::shared_ptr<Composite> component)
//{
//    if (component)
//    {
//        m_components[component->getName()] = component;
//        component->setOwner(this);
//        component->initialize();
//    }
//}
//
//void Hero::removeComponent(const std::string& name)
//{
//    m_components.erase(name);
//}
//
//Composite* Hero::getComponent(const std::string& name)
//{
//    return m_components.find(name) != m_components.end() ? m_components[name].get() : nullptr;
//}
//
//const Composite* Hero::getComponent(const std::string& name) const
//{
//    auto it = m_components.find(name);
//    return (it != m_components.end()) ? it->second.get() : nullptr;
//}
//
//ComponentGameObject* Hero::getComposite(const std::string& name)
//{
//    return getComposite(name);
//}
//
//float Hero::getSpeed() const
//{
//    return m_speed;
//}
//
//const sf::Vector2f& Hero::getPosition() const
//{
//    return m_position;
//}
//
//bool Hero::isGoingLeft() const
//{
//    return m_movingLeft;
//}
//
//bool Hero::isGoingRight() const
//{
//    return m_movingRight;
//}
//
//bool Hero::isGoingUp() const
//{
//    return m_movingUp;
//}
//
//bool Hero::isGoingDown() const
//{
//    return m_movingDown;
//}
//
//void Hero::setCategory(const std::string& category)
//{
//    m_category = category;
//}
//
//void Hero::addTag(const std::string& tag)
//{
//    m_tags.insert(tag);
//}
//
//bool Hero::hasTag(const std::string& tag) const
//{
//    return std::find(m_tags.begin(), m_tags.end(), tag) != m_tags.end();
//}
//
//void Hero::updateDirection()
//{
//    if (m_movingUp && !m_movingDown && !m_movingLeft && !m_movingRight)
//        setDirection(Direction::Up);
//    else if (!m_movingUp && m_movingDown && !m_movingLeft && !m_movingRight)
//        setDirection(Direction::Down);
//    else if (!m_movingUp && !m_movingDown && m_movingLeft && !m_movingRight)
//    {
//        setDirection(Direction::Left);
//        setFacingLeft(true);
//    }
//    else if (!m_movingUp && !m_movingDown && !m_movingLeft && m_movingRight)
//    {
//        setDirection(Direction::Right);
//        setFacingLeft(false);
//    }
//}
//
//bool Hero::isAttacking() const
//{
//    return m_attacking;
//}
//
//bool Hero::isShooting() const
//{
//    return m_shooting;
//}
//
//void Hero::knockBack(const sf::Vector2f& pos, float force)
//{
//    auto renderer = static_cast<SquareRenderer*>(getComponent("SquareRenderer"));
//    if (!renderer)
//        return;
//
//    sf::Vector2f heroPos = renderer->getPosition();
//
//    sf::Vector2f direction = heroPos - pos;
//
//    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
//    if (length > 0)
//    {
//        direction.x /= length;
//        direction.y /= length;
//    }
//    else
//        direction = sf::Vector2f(0, -1);
//
//    m_knockBack = direction * force;
//    m_knockBackDuration = 0.2f;
//}

#include "Hero.h"
#include "TextureManager.h"
#include "MyComposite.h"
#include "Animation.h"
#include "CollisionHitbox.h"
//#include "Effect.h"

Hero::Hero(const std::string& name)
    : ComponentGameObject(name)
    , m_health(100)
    , m_maxHealth(100)
    , m_armor(0)
    , m_strength(10)
    , m_currentStateName(stateName::idle)
    , m_currentDirection(Direction::Down)
    , m_isFacingLeft(false)
    , m_speed(200.0f)
    , m_stateManager(this)
{
    setCategory("Player");
    addTag("Hero");
}

void Hero::initialize(const sf::Vector2f& position, const float& size, const sf::Color& color, const float& speed)
{
    auto square_renderer = std::make_shared<SquareRenderer>(size, color);
    this->addComposite(square_renderer);
    square_renderer->setPosition(position);

    auto controller = std::make_shared<PlayerController>(speed);
    addComposite(controller);

    auto animation_component = std::make_shared<AnimationComponent>();
    addComposite(animation_component);

    auto hitbox = std::make_shared<Hitbox>(sf::Vector2f(60.f, 60.f));
    hitbox->setDebugDraw(false);
    addComposite(hitbox);

    m_speed = speed;

    m_stateManager.initialize();
}

void Hero::update(const float& deltaTime)
{
    if (m_knockBackDuration > 0)
    {
        m_knockBackDuration -= deltaTime;

        auto square_renderer = static_cast<SquareRenderer*>(getComposite("SquareRenderer"));
        if (square_renderer)
        {
            sf::Vector2f currentPos = square_renderer->getPosition();

            float slowdown_factor = std::min(1.0f, 4.0f * deltaTime);
            m_knockBack *= (1.0f - slowdown_factor);

            square_renderer->setPosition(currentPos + m_knockBack * deltaTime);
        }
    }

    ComponentGameObject::update(deltaTime);
    m_stateManager.update(deltaTime);
    updateAnimationPosition();
}

void Hero::updateAnimationPosition()
{
    auto square_renderer = static_cast<SquareRenderer*>(getComposite("SquareRenderer"));
    auto animation_component = static_cast<AnimationComponent*>(getComposite("AnimationComponent"));

    if (square_renderer && animation_component)
    {
        sf::Vector2f position = square_renderer->getPosition();
        animation_component->updatePosition(position);
    }
}

void Hero::processInput(const sf::Event& event)
{
    ComponentGameObject::processInput(event);
    m_stateManager.handleInput();
}

bool Hero::isAlive() const
{
    return m_health > 0;
}

void Hero::takeDamage(int amount, const sf::Vector2f& attackerPos)
{
    int actualDamage = amount - m_armor;
    if (actualDamage < 1)
        actualDamage = 1;

    m_health -= actualDamage;

    auto square_renderer = static_cast<SquareRenderer*>(getComposite("SquareRenderer"));
    if (square_renderer)
    {
        sf::Vector2f position = square_renderer->getPosition();
        sf::Vector2f entryDirection = position - attackerPos;
        sf::Vector2f bloodDirection = entryDirection;

        float length = std::sqrt(bloodDirection.x * bloodDirection.x + bloodDirection.y * bloodDirection.y);
        if (length > 0)
        {
            bloodDirection.x /= length;
            bloodDirection.y /= length;
        }
        else
            bloodDirection = sf::Vector2f(0, 1);

        /*BloodEffect::createBloodEffect(position, bloodDirection);*/
    }

    if (m_health <= 0)
    {
        m_health = 0;
        m_stateManager.changeState("Death");
    }
    else
        m_stateManager.changeState("Hurt");
}

void Hero::move(const sf::Vector2f& offset)
{
    auto square_renderer = static_cast<SquareRenderer*>(getComposite("SquareRenderer"));
    if (square_renderer)
    {
        sf::Vector2f currentPos = square_renderer->getPosition();
        square_renderer->setPosition(currentPos + offset);
    }
}

void Hero::setDirection(Direction direction)
{
    m_currentDirection = direction;

    if (direction == Direction::Left)
        m_isFacingLeft = true;
    else if (direction == Direction::Right)
        m_isFacingLeft = false;
}

Direction Hero::getDirection() const
{
    return m_currentDirection;
}

void Hero::setFacingLeft(bool left)
{
    m_isFacingLeft = left;

    if (left)
        m_currentDirection = Direction::Left;
    else
        m_currentDirection = Direction::Right;
}

void Hero::attack()
{
    m_stateManager.changeState("Attack");
}

void Hero::shoot()
{
    m_stateManager.changeState("Shoot");
}

stateName Hero::getCurrentState() const
{
    return m_currentStateName;
}

void Hero::setState(stateName newState)
{
    m_currentStateName = newState;

    auto animation_component = static_cast<AnimationComponent*>(getComposite("AnimationComponent"));
    if (!animation_component)
        return;

    std::string direction_suffix;
    switch (m_currentDirection)
    {
    case Direction::Up:
        direction_suffix = "_up";
        break;
    case Direction::Down:
        direction_suffix = "_down";
        break;
    case Direction::Right:
    case Direction::Left:
        direction_suffix = "_right";
        break;
    }

    if (newState == stateName::hurt)
    {
        animation_component->playAnimation("hurt");
        return;
    }

    if (newState == stateName::death)
    {
        animation_component->playAnimation("death");
        return;
    }

    switch (newState)
    {
    case stateName::idle:
        animation_component->playAnimation("idle" + direction_suffix);
        break;
    case stateName::run:
        animation_component->playAnimation("run" + direction_suffix);
        break;
    case stateName::attack:
        animation_component->playAnimation("attack" + direction_suffix);
        break;
    case stateName::shoot:
        animation_component->playAnimation("shoot" + direction_suffix);
        break;
    default:
        break;
    }

    if (m_isFacingLeft && (m_currentDirection == Direction::Left || m_currentDirection == Direction::Right))
        animation_component->setScale(sf::Vector2f(-2.0f, 2.0f));
    else
        animation_component->setScale(sf::Vector2f(2.0f, 2.0f));
}

float Hero::getSpeed() const
{
    return m_speed;
}

bool Hero::isFacingLeft() const
{
    return m_isFacingLeft;
}

HeroState& Hero::getStateManager()
{
    return m_stateManager;
}

void Hero::knockBack(const sf::Vector2f& pos, float force)
{
    if (m_currentStateName == stateName::death)
    {
        m_knockBackDuration = 0.f;
        m_knockBack = sf::Vector2f(0.f, 0.f);
        return;
    }

    auto square_renderer = static_cast<SquareRenderer*>(getComposite("SquareRenderer"));
    if (!square_renderer)
        return;

    sf::Vector2f heroPos = square_renderer->getPosition();

    sf::Vector2f direction = heroPos - pos;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0)
    {
        direction.x /= length;
        direction.y /= length;
    }
    else
        direction = sf::Vector2f(0, -1);

    m_knockBack = direction * force;
    m_knockBackDuration = 0.2f;
}

int Hero::getHealth() const
{
    return m_health;
}

int Hero::getMaxHealth() const
{
    return m_maxHealth;
}

float Hero::getHealthPercentage() const
{
    if (m_maxHealth <= 0)
        return 0.0f;

    return static_cast<float>(m_health) / static_cast<float>(m_maxHealth);
}

void Hero::setMaxHealth(int maxHealth)
{
    m_maxHealth = maxHealth;
    if (m_health > m_maxHealth)
        m_health = m_maxHealth;
}

void Hero::heal(int amount)
{
    m_health += amount;
    if (m_health > m_maxHealth)
        m_health = m_maxHealth;
}