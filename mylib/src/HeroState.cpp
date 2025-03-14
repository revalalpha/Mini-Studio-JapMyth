#include "HeroState.h"

// IDLE STATE
void IdleState::handleInput(Hero& hero) {
    if (isGoingLeft() || isGoingRight()) hero.setState(HeroStateNames::stateName::run);
    updateDirection(hero);
    if (isAttacking()) hero.setState(HeroStateNames::stateName::attack);
    if (isBlocking()) hero.setState(HeroStateNames::stateName::block);
}

void IdleState::update(Hero& hero, float deltaTime) {
    updateAnimation(hero);
}

void IdleState::setTexture(Hero& hero) {
    hero.getSprite().setTexture(hero.getTexture(HeroStateNames::stateName::idle));
}

// RUN STATE
void RunState::handleInput(Hero& hero) {
    if ((!isGoingRight() && !isGoingLeft()) || (isGoingRight() && isGoingLeft()))
        hero.setState(HeroStateNames::stateName::idle);
    if (isDodging()) hero.setState(HeroStateNames::stateName::dodge);
    if (isAttacking()) hero.setState(HeroStateNames::stateName::attack);
    updateDirection(hero);
}

void RunState::update(Hero& hero, float deltaTime) {
    moveHero(hero, deltaTime);
    updateAnimation(hero);
}

void RunState::setTexture(Hero& hero) {
    hero.getSprite().setTexture(hero.getTexture(HeroStateNames::stateName::run));
}

// ATTACK STATE
void AttackState::handleInput(Hero& hero) {
    updateDirection(hero);
}

void AttackState::update(Hero& hero, float deltaTime) {
    if (updateAnimation(hero)) {
        if (isGoingLeft() || isGoingRight()) hero.setState(HeroStateNames::stateName::run);
        else hero.setState(HeroStateNames::stateName::idle);
    }
}

void AttackState::setTexture(Hero& hero) {
    hero.getSprite().setTexture(hero.getTexture(HeroStateNames::stateName::attack));
}

// BLOCK STATE
void BlockState::handleInput(Hero& hero) {
    if (isDodging()) hero.setState(HeroStateNames::stateName::dodge);
    if (isAttacking()) hero.setState(HeroStateNames::stateName::attack);
    updateDirection(hero);
}

void BlockState::update(Hero& hero, float deltaTime) {
    if (!isBlocking()) {
        hero.setState(isMoving() ? HeroStateNames::stateName::run : HeroStateNames::stateName::idle);
        return;
    }
    updateAnimation(hero);
}

void BlockState::setTexture(Hero& hero) {
    hero.getSprite().setTexture(hero.getTexture(HeroStateNames::stateName::block));
}

// DODGE STATE
void DodgeState::handleInput(Hero& hero) {
    if (elapsedTimeExceeds(m_dodgeDuration)) {
        hero.getAirDodge(false);
        hero.setState(isMoving() ? HeroStateNames::stateName::run : HeroStateNames::stateName::idle);
    }
}

void DodgeState::update(Hero& hero, float deltaTime) {
    executeDodge(hero, deltaTime);
    updateAnimation(hero);
}

void DodgeState::setTexture(Hero& hero) {
    hero.getSprite().setTexture(hero.getTexture(HeroStateNames::stateName::dodge));
}

// HURT STATE
void HurtState::handleInput(Hero& hero) {
    if (elapsedTimeExceeds(m_hurtDuration))
        hero.setState(isMoving() ? HeroStateNames::stateName::run : HeroStateNames::stateName::idle);
}

void HurtState::update(Hero& hero, float deltaTime) {
    if (elapsedTimeExceeds(m_hurtDuration)) {
        hero.setState(isMoving() ? HeroStateNames::stateName::run : HeroStateNames::stateName::idle);
        return;
    }
    updateAnimation(hero);
}

void HurtState::setTexture(Hero& hero) {
    hero.getSprite().setTexture(hero.getTexture(HeroStateNames::stateName::hurt));
}

// DEATH STATE
void DeathState::handleInput(Hero& hero) {}

void DeathState::update(Hero& hero, float deltaTime) {
    if (updateAnimation(hero)) m_animationComplete = true;
}

void DeathState::setTexture(Hero& hero) {
    hero.getSprite().setTexture(hero.getTexture(HeroStateNames::stateName::death));
}
