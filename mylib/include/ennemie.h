#ifndef IENNEMIES_H
#define IENNEMIES_H

#include "behaviorTree.h"
#include "gameObject.h"
#include "game.h"
#include <unordered_map>
#include <functional>

namespace EnnemieState
{
    enum class State
    {
        Run,
        Attack,
        Death

    };
}

struct AnimationData
{
    int frameCount;
    float frameDuration;
};

class IEnnemies : public IGameObject
{
public:
    using State = EnnemieState::State;

    IEnnemies(Game* game, int health);
    virtual ~IEnnemies() = default;

    virtual void initializeBehaviorTree() = 0;
    virtual void update(float deltaTime);
    virtual void takeDamage(int damage) override;
    virtual void attack();
    virtual bool isAlive() override;
    virtual bool isInvulnerable() override;
    virtual void draw(sf::RenderWindow& window) const;

    void setState(State newState);
    State getState() const;
    int getAttackDamage(State attackType) const;
    sf::Sprite& getSprite();
    sf::Texture& getTexture(const State& stateName_);

protected:
    Game* m_game;
    Hero* m_currentTarget;
    int m_health;
    bool m_isInvulnerable;
    float m_invulnerableDuration;
    BT::RootNode m_rootNode;
    State m_currentState;
    std::unordered_map<State, AnimationData> m_animations;
    std::unordered_map<State, sf::Texture> m_textures;
    sf::Sprite m_sprites;
    int attackDamage = 10;

    std::map<State, sf::Texture> m_texturesE1;
};

class Ennemie1 : public IEnnemies
{
public:
    virtual void initializeBehaviorTree() = 0;
    virtual void update(float deltaTime);
    virtual void takeDamage(int damage) override;
    virtual void attack();
    virtual bool isAlive() override;
    virtual bool isInvulnerable() override;
    virtual void draw(sf::RenderWindow& window) const;

};


#endif // IENNEMIES_H
