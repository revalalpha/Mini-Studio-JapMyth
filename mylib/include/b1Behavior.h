#pragma once

#include "behaviorTree.h"
#include "boss.h"
#include "game.h"

class Game;

namespace BT
{
    class IfHealthLow : public BehaviorNodeDecorator<class Boss, IConditionalNode>
    {
    public:
        IfHealthLow(ICompositeNode* node) : BehaviorNodeDecorator(node) {}
        bool condition() override
        {
            return getGameObject()->getHp() < 100;
        }
    };

    class BossAttack1 : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    private:
        Game* m_game;
    public:
        BossAttack1(ICompositeNode* parent, Game* game)
            : BehaviorNodeDecorator(parent), m_game(game) {}

        Status tick() override
        {
            if (m_game)
            {
                Hero& player = m_game->getPlayer();
                if (player.getHp() <= 0)
                {
                    getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Idle);
                    std::cout << "Hero is dead!" << std::endl;
                    return Failed;
                }
            }
            getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Attack1);
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseOne::Attack1);
            if (m_game)
                m_game->getPlayer().takeDamage(damage);

            return Success;
        }
    };

    class BossAttack2 : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    private:
        Game* m_game;
    public:
        BossAttack2(ICompositeNode* parent, Game* game)
            : BehaviorNodeDecorator(parent), m_game(game) {}

        Status tick() override
        {
            if (m_game)
            {
                Hero& player = m_game->getPlayer();
                if (player.getHp() <= 0)
                {
                    getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Idle);
                    std::cout << "Hero is dead!" << std::endl;
                    return Failed;
                }
            }
            getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Attack2);
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseOne::Attack2);
            if (m_game)
                m_game->getPlayer().takeDamage(damage);

            return Success;
        }
    };

    class CheckTargetInRange : public IConditionalNode
    {
    private:
        float m_range;
    public:
        CheckTargetInRange(ICompositeNode* parent, float range)
            : IConditionalNode(parent), m_range(range)
        {}

        bool condition() override
        {
            auto boss = dynamic_cast<class Boss*>(getGameObject());
            if (!boss || !boss->getCurrentTarget())
                return false;

            sf::Vector2f bossPos = boss->getSprite().getPosition();
            sf::Vector2f targetPos = boss->getCurrentTarget()->getPlayerPosition();
            float dx = bossPos.x - targetPos.x;
            float dy = bossPos.y - targetPos.y;
            float dist = std::sqrt(dx * dx + dy * dy);
            return dist <= m_range;
        }

        void display() override
        {
            std::cout << "CheckTargetInRange: range = " << m_range << std::endl;
        }
    };

    class RunTowardsTarget : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    private:
        bool m_isPlayer;
    public:
        RunTowardsTarget(ICompositeNode* parent, bool isPlayer)
            : BehaviorNodeDecorator(parent), m_isPlayer(isPlayer) {}

        Status tick() override
        {
            if (!getGameObject()->getCurrentTarget())
                return Failed;

            if (getGameObject()->getHitbox().intersects(getGameObject()->getCurrentTarget()->getHitbox()))
                return Success;

            getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Run);
            auto target = getGameObject()->getCurrentTarget()->getPlayerPosition();
            auto currentPos = getGameObject()->getSprite().getPosition();

            float moveSpeed = 200.0f;
            sf::Vector2f direction = target - currentPos;
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            float minSafeDistance = 80.0f;

            if (distance > minSafeDistance)
            {
                direction /= distance;
                sf::Vector2f movement = direction * moveSpeed * 0.015f;

                if (direction.x > 0)
                {
                    getGameObject()->isFacingLeft(false);
                    getGameObject()->getSprite().setScale(2.f, 2.f);
                }
                else
                {
                    getGameObject()->isFacingLeft(true);
                    getGameObject()->getSprite().setScale(-2.f, 2.f);
                }

                getGameObject()->getSprite().move(movement);
            }
            return Running;

        }
    };

    class AttackOrChaseSelector : public ICompositeNode
    {
    public:
        AttackOrChaseSelector(ICompositeNode* parent)
            : ICompositeNode(parent)
        {}

        Status tick() override
        {
            for (auto child : getChildren())
            {
                Status status = child->tick();
                if (status == Success || status == Running)
                    return status;
            }
            return Failed;
        }

        void display() override
        {
            for (auto child : getChildren())
                child->display();
        }
    };

    class Idle : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    public:
        Idle(ICompositeNode* parent) : BehaviorNodeDecorator(parent) {}
        Status tick() override
        {
            getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Idle);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture(Boss::BossStatePhaseOne::Idle));
            return Success;
        }
    };

    class Hurt : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    public:
        Hurt(ICompositeNode* parent) : BehaviorNodeDecorator(parent) {}
        Status tick() override
        {
            getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Hurt);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture(Boss::BossStatePhaseOne::Hurt));
            return Success;
        }
    };

    class Death : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    public:
        Death(ICompositeNode* parent) : BehaviorNodeDecorator(parent) {}
        Status tick() override
        {
            getGameObject()->setStatePhaseTwo(Boss::BossStatePhaseTwo::Death);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture2(Boss::BossStatePhaseTwo::Death));
            return Success;
        }
    };

    class Wait : public IActionNode
    {
    private:
        sf::Time m_duration;
        sf::Clock m_timer;
        bool m_started = false;

    public:
        Wait(ICompositeNode* parent, float duration)
            : IActionNode(parent), m_duration(sf::seconds(duration)) {}

        Status tick() override
        {
            if (!m_started)
            {
                m_started = true;
                m_timer.restart();
            }

            if (m_timer.getElapsedTime() >= m_duration)
            {
                reset();
                return Success;
            }

            return Running;
        }

        void reset()
        {
            m_started = false;
            m_timer.restart();
        }
    };
}