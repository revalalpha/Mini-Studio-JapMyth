#ifndef HERO_STATES_H
#define HERO_STATES_H

#include <SFML/Graphics.hpp>
#include "hero.h"

class Hero;

class IState
{
public:
    virtual ~IState() = default;
    virtual void handleInput(Hero& hero) = 0;
    virtual void update(Hero& hero, float deltaTime) = 0;
    virtual void setTexture(Hero& hero) = 0;
    virtual bool isTemporaryState() const { return false; }

    static bool isGoingLeft();
    static bool isGoingRight();
    static bool isJumping();
    static bool isDodging();
    static bool canDodge();
    static bool isAttacking();
    static bool isBlocking();
    static void updateDirection(Hero& hero);

protected:
    static bool m_dashAvailable;
    static sf::Clock m_dashCooldownClock;
    static const float m_dashCooldownDuration;
    static bool m_mouseLeftPressed;
};

class IdleState : public IState {
public:
    void handleInput(Hero& hero) override;
    void update(Hero& hero, float deltaTime) override;
    void setTexture(Hero& hero) override;
};

class AttackState : public IState {
public:
    void handleInput(Hero& hero) override;
    void update(Hero& hero, float deltaTime) override;
    void setTexture(Hero& hero) override {}
};

class BlockState : public IState {
public:
    void handleInput(Hero& hero) override;
    void update(Hero& hero, float deltaTime) override;
    void setTexture(Hero& hero) override;
};

class RunState : public IState {
public:
    void handleInput(Hero& hero) override;
    void update(Hero& hero, float deltaTime) override;
    void setTexture(Hero& hero) override;
};

class DodgeState : public IState {
public:
    void handleInput(Hero& hero) override;
    void update(Hero& hero, float deltaTime) override;
    void setTexture(Hero& hero) override;
private:
    sf::Clock m_elapsedTime;
    const float m_dodgeDuration = 0.5f;
    const float m_dodgeSpeed = 300.f;
};

class HurtState : public IState {
private:
    sf::Clock m_hurtTimer;
    const float m_hurtDuration = 0.5f;

public:
    void handleInput(Hero& hero) override;
    void update(Hero& hero, float deltaTime) override;
    void setTexture(Hero& hero) override;
};

class DeathState : public IState {
private:
    bool m_animationComplete = false;

public:
    void handleInput(Hero& hero) override;
    void update(Hero& hero, float deltaTime) override;
    void setTexture(Hero& hero) override;
};

#endif // HERO_STATES_H
