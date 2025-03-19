//#pragma once
//#include <memory>
//#include <map>
//#include <string>
//#include "Hero.h"
//
//namespace StatesHero
//{
//	enum class HeroStateName;
//}
//
//class Hero;
//class IState;
//
//enum class Direction;
//enum class stateName;
//
//class HeroState
//{
//public:
//    HeroState(Hero* owner);
//    ~HeroState();
//
//    void initialize();
//    void update(float deltaTime);
//    void handleInput();
//
//    void changeState(StatesHero::HeroStateName stateName);
//    StatesHero::HeroStateName getCurrentState() const;
//
//private:
//    std::map<StatesHero::HeroStateName, std::unique_ptr<IState>> m_states;
//    IState* m_currentState;
//    StatesHero::HeroStateName m_currentStateName;
//    Hero* m_owner;
//};
#pragma once

#include <memory>
#include <map>
#include <string>
#include "StateManager.h"
#include "State.h"
#include "Hero.h"
#include "Animation.h"
#include "MyComponent.h"

class Hero;
class IState;

enum class Direction;
enum class stateName;

class HeroState
{
public:
    HeroState(Hero* owner);
    ~HeroState();
    void initialize();
    void update(float deltaTime);
    void handleInput();
    void changeState(const std::string& stateName);
    std::string getCurrentStateName() const;
private:
    std::map<std::string, std::unique_ptr<State<Hero>>> m_states;
    State<Hero>* m_currentState;
    std::string m_currentStateName;
    Hero* m_owner;
};

class IdleState : public State<Hero>
{
public:
    IdleState(Hero* owner) : m_owner(owner) {}

    void enter(Hero& owner) override;
    void handleInput(Hero& owner) override;
    void update(Hero& owner, float deltaTime) override {}
    void exit(Hero& owner) override {}

private:
    Hero* m_owner;
};

class RunState : public State<Hero>
{
public:
    RunState(Hero* owner) : m_owner(owner) {}

    void enter(Hero& owner) override;
    void handleInput(Hero& owner) override;
    void update(Hero& owner, float deltaTime) override;
    void exit(Hero& owner) override {}

private:
    Hero* m_owner;
};

class AttackState : public State<Hero>
{
public:
    AttackState(Hero* owner) : m_owner(owner) {}

    void enter(Hero& owner) override;
    void handleInput(Hero& owner) override {}
    void update(Hero& owner, float deltaTime) override;
    void exit(Hero& owner) override {}

private:
    Hero* m_owner;
    sf::Clock m_animClock;
};

class ShootState : public State<Hero>
{
public:
    ShootState(Hero* owner) : m_owner(owner) {}

    void enter(Hero& owner) override;
    void handleInput(Hero& owner) override {}
    void update(Hero& owner, float deltaTime) override;
    void exit(Hero& owner) override {}

private:
    Hero* m_owner;
    sf::Clock m_animClock;
};

class HurtState : public State<Hero>
{
public:
    HurtState(Hero* owner) : m_owner(owner) {}

    void enter(Hero& owner) override;
    void handleInput(Hero& owner) override {}
    void update(Hero& owner, float deltaTime) override;
    void exit(Hero& owner) override {}

private:
    Hero* m_owner;
    sf::Clock m_animClock;
    float m_hurtDuration = 1.0f;
};

class DeathState : public State<Hero>
{
public:
    DeathState(Hero* owner) : m_owner(owner) {}

    void enter(Hero& owner) override;
    void handleInput(Hero& owner) override {}
    void update(Hero& owner, float deltaTime) override {}
    void exit(Hero& owner) override {}

private:
    Hero* m_owner;
};

