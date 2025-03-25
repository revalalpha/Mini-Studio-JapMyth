//#pragma once
//
//#include <SFML/Graphics.hpp>
//#include <string>
//#include "HeroState.h"
//#include "CollisionHitbox.h"
//#include "StateFactory.h"
//#include "StateManager.h"
//#include "MyComponent.h"
//
//enum class Direction
//{
//    Up,
//    Down,
//    Left,
//    Right
//};
//
//enum class stateName
//{
//    idle,
//    run,
//    meleeAttack,
//    rangeAttack,
//    hurt,
//    death
//};
//
//class Hero : public ComponentGameObject
//{
//public:
//    Hero(const std::string& name = "Hero");
//    ~Hero();
//
//    void initialize(const sf::Vector2f& position, float size, const sf::Color& color, float speed);
//    void update(const float& deltaTime) override;
//    void processInput(const sf::Event& event) override;
//    void render(sf::RenderWindow& window) override;
//    void handleInputs(const sf::Event& event) override;
//
//    bool isAlive() const;
//    bool isFacingLeft() const;
//    void takeDamage(int amount);
//    void move(const sf::Vector2f& offset);
//    void setFacingLeft(bool left);
//    void setDirection(Direction dir);
//    Direction getDirection() const;
//    sf::Sprite& getSprite();
//    sf::Vector2f getPosition();
//    void handleInput();
//
//    void attack();
//    void shoot();
//
//    stateName getCurrentState() const;
//    void setState(stateName newState);
//
//    HeroState& getStateManager();
//    float getSpeed() const;
//    const sf::Vector2f& getPosition() const;
//
//    bool isGoingLeft() const;
//    bool isGoingRight() const;
//    bool isGoingUp() const;
//    bool isGoingDown() const;
//    void updateDirection();
//
//    bool isAttacking() const;
//    bool isShooting() const;
//
//    void addComponent(std::shared_ptr<Composite> component);
//    void removeComponent(const std::string& name);
//    Composite* getComponent(const std::string& name);
//    const Composite* getComponent(const std::string& name) const;
//    ComponentGameObject* getComposite(const std::string& name);
//    void setCategory(const std::string& category);
//    void addTag(const std::string& tag);
//    bool hasTag(const std::string& tag) const;
//    void knockBack(const sf::Vector2f& pos, float force);
//
//    void updateComponents(const float& deltaTime);
//    void updateAnimationPosition();
//    void updateAnimation(stateName newState);
//
//
//private:
//    Direction m_currentDirection;
//    float m_knockBackDuration;
//    bool m_isFacingLeft;
//    sf::Sprite m_sprite;
//    int m_health;
//    int m_armor;
//    int m_strength;
//    stateName m_currentStateName;
//    float m_speed;
//    sf::Vector2f m_position;
//    HeroState m_stateManager;
//    sf::Vector2f m_knockBack;
//    std::unordered_map<std::string, std::shared_ptr<Composite>> m_components;
//
//    static constexpr int idleFrameCount = 2;
//    static constexpr int runFrameCount = 2;
//    static constexpr int shootFrameCount = 4;
//    static constexpr int attackFrameCount = 6;
//    static constexpr int hurtFrameCount = 1;
//    static constexpr int deathFrameCount = 18;
//
//    bool m_movingLeft = false;
//    bool m_movingRight = false;
//    bool m_movingUp = false;
//    bool m_movingDown = false;
//    bool m_attacking = false;
//    bool m_shooting = false;
//};

#pragma once
#include "MyComposite.h"
#include "HeroState.h"
#include "MyComponent.h"

enum class Direction
{
    Up,
    Down,
    Left,
    Right
};

enum class stateName
{
    idle,
    run,
    attack,
    shoot,
    hurt,
    death
};

class Hero : public ComponentGameObject
{
public:
    Hero(const std::string& name = "Hero");
    ~Hero() = default;

    void initialize(const sf::Vector2f& position, const float& size,
        const sf::Color& color, const float& speed);

    void updateAnimationPosition();

    void update(const float& deltaTime) override;
    void processInput(const sf::Event& event) override;
    //void render(sf::RenderWindow& window)override;

    bool isAlive() const;
    bool isFacingLeft() const;

    void takeDamage(int amount, const sf::Vector2f& attackerPos);
    void move(const sf::Vector2f& offset);
    void setFacingLeft(bool left);
    void setDirection(Direction direction);
    Direction getDirection() const;

    void attack();
    void shoot();

    stateName getCurrentState() const;
    void setState(stateName newState);

    float getSpeed() const;

    HeroState& getStateManager();

    void knockBack(const sf::Vector2f& pos, float force);

    int getHealth() const;
    int getMaxHealth() const;
    float getHealthPercentage() const;
    void setMaxHealth(int maxHealth);
    void heal(int amount);

private:
    int m_health;
    int m_maxHealth;
    int m_armor;
    int m_strength;

    stateName m_currentStateName;
    Direction m_currentDirection;

    bool m_isFacingLeft;

    float m_speed;

    HeroState m_stateManager;

private:
    sf::Vector2f m_knockBack;
    float m_knockBackDuration = 0.0f;
};