#pragma once

#include "behaviorTree.h"
#include "ennemie.h"

class Game;

namespace BT
{
    class Run : public IActionNode
    {
    public:
        Run(ICompositeNode* parent) : IActionNode(parent) {}

        Status tick() override
        {
            return Success;
        }
    };

    class Chase : public IActionNode
    {
    public:
        Chase(ICompositeNode* parent) : IActionNode(parent) {}

        Status tick() override
        {
            return Success;
        }
    };

    class Attack : public BehaviorNodeDecorator<class IEnnemies, IActionNode>
    {
    private:
        Game* m_game;
    public:
        Attack(ICompositeNode* parent, Game* game) : BehaviorNodeDecorator(parent), m_game(game) {}

        Status tick() override
        {
            if (m_game)
            {
                Hero& player = m_game->getPlayer();
                if (player.getHp() <= 0)
                {
                    std::cout << "Hero is dead!" << std::endl;
                    return Failed;
                }
            }
            getGameObject()->setState(IEnnemies::State::Attack);
            int damage = getGameObject()->getAttackDamage(IEnnemies::State::Attack);
            if (m_game)
                m_game->getPlayer().takeDamage(damage);

            return Success;
        }
    };

    class Death : public BehaviorNodeDecorator<class IEnnemies, IActionNode>
    {
    public:
        Death(ICompositeNode* parent) : BehaviorNodeDecorator(parent) {}
        Status tick() override
        {
            getGameObject()->setState(IEnnemies::State::Death);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture(IEnnemies::State::Death));
            return Success;
        }
    };
}