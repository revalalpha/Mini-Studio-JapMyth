#pragma once

#include "IGameObject.h"
#include "Tree.h"
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "PlayerShip.h"

class IGameObjectContainer;


namespace SamuraiStateNames
{
    enum class SamuraiState
    {
        Idle,
        sprint,
        Hurt,
        MeleeAttack,
        DistanceAttack,
        walk,
    };
}







class Samurai : public IGameObject
{
public:
    Samurai(IGameObjectContainer& game, const Vec2& position);

    void handleInputs(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    OBB getBoundingBox() const override;
    GameObjectType gameObjectType() override;
    void takeDamage(int dmg = 1);
    void die();

    void fireWithPistol();
    void RightMelee();


    bool findValidTarget();
    bool isCurrentTargetValid() const;
    void setSpeed(const int& Speed);
    float calculateAngleToTarget() const;


    Vec2 getPosition() const;
    Vec2 getDistanceToPlayer() const;
    float getAngle()const;

    int getHP()const;
    int getMaxHP()const;


    float SpeedLimit = 0;

private:
    SamuraiStateNames::SamuraiState* m_currentState;

    int m_speed = 0;
    float m_angle;

    int m_HP = 2;
    int m_MaxHP = m_HP;
    bool m_isDead = false;
    bool m_isInvincible = false;
    const float m_invincibility = 0.1f;
    sf::Clock m_clockHit;
    sf::Time m_elapsedTimeHit;

    sf::Texture m_spriteSheet;
    sf::Sprite m_sprite;
    BT::RootNode m_rootNode;
    Vec2 m_position;
    Vec2 m_velocity = { 0.f,0.f };
    std::vector<IGameObject*> m_allGameObjects;
    PlayerShip* m_currentTarget;



    SheetToBeAnimated testtt;
    
};