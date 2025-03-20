#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "HeroState.h"
#include "StateFactory.h"
#include "StateManager.h"
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
    meleeAttack,
    rangeAttack,
    hurt,
    death
};

class Hero : public ComponentGameObject
{
public:
    Hero(const std::string& name = "Hero");
    ~Hero();

    void initialize(const sf::Vector2f& position, float size, const sf::Color& color, float speed);
    void update(const float& deltaTime) override;
    void processInput(const sf::Event& event) override;

    void handleInputs(const sf::Event& event) override;

    bool isAlive() const;
    bool isFacingLeft() const;
    void takeDamage(int amount);
    void move(const sf::Vector2f& offset);
    void setFacingLeft(bool left);
    void setDirection(Direction dir);
    Direction getDirection() const;
    sf::Sprite& getSprite();
    void handleInput();

    void attack();
    void shoot();

    stateName getCurrentState() const;
    void setState(stateName newState);

    StateManager& getStateManager();
    float getSpeed() const;
    const sf::Vector2f& getPosition() const;

    bool isGoingLeft() const;
    bool isGoingRight() const;
    bool isGoingUp() const;
    bool isGoingDown() const;
    void updateDirection();

    bool isAttacking() const;
    bool isShooting() const;

    void addComponent(std::shared_ptr<Composite> component);
    void removeComponent(const std::string& name);
    Composite* getComponent(const std::string& name);
    const Composite* getComponent(const std::string& name) const;


private:
    Direction m_currentDirection;
    bool m_isFacingLeft;
    sf::Sprite m_sprite;
    int m_health;
    int m_armor;
    int m_strength;
    stateName m_currentStateName;
    float m_speed;
    sf::Vector2f m_position;
    StateManager m_stateManager;
    std::unordered_map<std::string, std::shared_ptr<Composite>> m_components;

    static constexpr int idleFrameCount = 2;
    static constexpr int runFrameCount = 2;
    static constexpr int shootFrameCount = 4;
    static constexpr int attackFrameCount = 6;
    static constexpr int hurtFrameCount = 1;
    static constexpr int deathFrameCount = 18;

    bool m_movingLeft = false;
    bool m_movingRight = false;
    bool m_movingUp = false;
    bool m_movingDown = false;
    bool m_attacking = false;
    bool m_shooting = false;
};
