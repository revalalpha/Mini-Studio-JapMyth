//#include "Ennemy.h"
//
//BaseEnemy::BaseEnemy(const std::string& name, const sf::Vector2f& position, int health, float speed)
//    : m_name(name), m_position(position), m_health(health), m_speed(speed)
//{}
//
//void BaseEnemy::update(float deltaTime) override
//{
//    if (m_behaviorTree)
//        m_behaviorTree->tick();
//    move(deltaTime);
//}
//
//void BaseEnemy::render(sf::RenderWindow& window) override
//{
//}
//
//void BaseEnemy::processInput(const sf::Event& event) override
//{
//}
//
//void BaseEnemy::setPosition(const sf::Vector2f& position) override
//{
//    m_position = position;
//}
//
//sf::Vector2f BaseEnemy::getPosition() const override
//{
//    return m_position;
//}
//
//std::string BaseEnemy::getName() const override
//{
//    return m_name;
//}
//
//void BaseEnemy::takeDamage(int amount)
//{
//    m_health -= amount;
//    if (m_health <= 0)
//    {
//        die();
//    }
//}
//
//void BaseEnemy::move(float deltaTime)
//{
//}