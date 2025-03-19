//#pragma once
//
//#include <SFML/Graphics.hpp>
//#include <string>
//#include <memory>
//#include <vector>
//#include "Tree.h"
//#include "EnnemyBT.h"
//
//class IEnemy
//{
//public:
//    virtual ~IEnemy() = default;
//    virtual void update(float deltaTime) = 0;
//    virtual void render(sf::RenderWindow& window) = 0;
//    virtual void processInput(const sf::Event& event) = 0;
//    virtual void setPosition(const sf::Vector2f& position) = 0;
//    virtual sf::Vector2f getPosition() const = 0;
//    virtual std::string getName() const = 0;
//    virtual sf::Vector2f getPlayerPosition() const = 0;
//    virtual float getSpeed() const = 0;
//    virtual bool isCurrentTargetValid() const = 0;
//    virtual void performAttack() = 0;
//    virtual void die() = 0;
//    virtual int getHP() const = 0;
//    virtual sf::Vector2f getDistanceToPlayer() const = 0;
//    virtual void fireProjectile() = 0;
//    static void updateAllEnemyLOS(std::vector<std::shared_ptr<IEnemy>>& enemies, const sf::Vector2f& playerPos);
//};
//
//class BaseEnemy : public IEnemy
//{
//public:
//    BaseEnemy(const std::string& name, const sf::Vector2f& position, int health, float speed);
//    virtual ~BaseEnemy() = default;
//    void update(float deltaTime) override;
//    void render(sf::RenderWindow& window) override;
//    void processInput(const sf::Event& event) override;
//    void setPosition(const sf::Vector2f& position) override;
//    sf::Vector2f getPosition() const override;
//    std::string getName() const override;
//	void takeDamage(int amount);
//	virtual void move(float deltaTime);
//
//protected:
//    std::string m_name;
//    sf::Vector2f m_position;
//    int m_health;
//    float m_speed;
//    std::unique_ptr<BT::BehaviorTree> m_behaviorTree;
//};
//
//class SamuraiEnemy : public BaseEnemy
//{
//public:
//    SamuraiEnemy(const sf::Vector2f& position)
//        : BaseEnemy("Samurai", position, 100, 3.0f)
//    {
//        m_behaviorTree = std::make_unique<BT::SamuraiBT::MoveAndAttackSequence>(nullptr, position);
//    }
//
//    void update(float deltaTime) override
//    {
//        BaseEnemy::update(deltaTime);
//    }
//
//    void render(sf::RenderWindow& window) override
//    {
//    }
//};
//
//
//class KappaEnemy : public BaseEnemy
//{
//public:
//    KappaEnemy(const sf::Vector2f& position)
//        : BaseEnemy("Kappa", position, 120, 2.5f)
//    {
//        m_behaviorTree = std::make_unique<BT::KappaBT::MoveAndShootSequence>(nullptr, position);
//    }
//
//    void update(float deltaTime) override
//    {
//        BaseEnemy::update(deltaTime);
//    }
//
//    void render(sf::RenderWindow& window) override
//    {
//    }
//};
//
//void IEnemy::updateAllEnemyLOS(std::vector<std::shared_ptr<IEnemy>>& enemies, const sf::Vector2f& playerPos)
//{
//    for (auto& enemy : enemies)
//    {
//        if (enemy)
//        {
//            sf::Vector2f enemyPos = enemy->getPosition();
//            float distance = std::sqrt(std::pow(playerPos.x - enemyPos.x, 2) + std::pow(playerPos.y - enemyPos.y, 2));
//
//            if (distance < 300.0f)
//                std::cout << enemy->getName() << " palyer in range " << std::endl;
//        }
//    }
//}