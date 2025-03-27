#pragma once
#pragma once

#include "Tree.h"
#include "Boss1.h"




namespace BT
{

    class WaitBoss1 : public IActionNode
    {
    private:
        sf::Time m_duration;
        sf::Clock m_timer;
        bool m_started = false;

    public:
        WaitBoss1(ICompositeNode* parent, float duration)
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

    class WalkBoss1 : public BehaviorNodeDecorator<Boss1, IActionNode>
    {
    public:
        WalkBoss1(ICompositeNode* parent) : BehaviorNodeDecorator<Boss1, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            getGameObject()->setSpeed(500);
            getGameObject()->SpeedLimit = 100.f;
            return Success;
        }


    };

    class SprintBoss1 : public BehaviorNodeDecorator<Boss1, IActionNode>
    {
    public:
        SprintBoss1(ICompositeNode* parent) : BehaviorNodeDecorator<Boss1, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            getGameObject()->setSpeed(1000);
            getGameObject()->SpeedLimit = 400.f;
            return Success;
        }


    };
    class IdleBoss1 : public BehaviorNodeDecorator<Boss1, IActionNode>
    {
    public:
        IdleBoss1(ICompositeNode* parent) : BehaviorNodeDecorator<Boss1, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            getGameObject()->setSpeed(0);
            getGameObject()->SpeedLimit = 100.f;
            return Success;
        }


    };

    class IsPlayerDeadBoss1 : public BehaviorNodeDecorator<Boss1, IActionNode>
    {
    public:
        IsPlayerDeadBoss1(ICompositeNode* parent) : BehaviorNodeDecorator<Boss1, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            if (!getGameObject()->isCurrentTargetValid())
            {
                return Success;
            }
            return Failed;

        }
    };







    class MeleeBoss1 : public BehaviorNodeDecorator<Boss1, IActionNode>
    {
    public:
        MeleeBoss1(ICompositeNode* parent) : BehaviorNodeDecorator<Boss1, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            
            if (!getGameObject()->isCurrentTargetValid())
                return Failed;

            if (m_delay == 0)
            {
                getGameObject()->RightMelee();
                m_delay = 50;
                return Success;
            }
            m_delay--;

            return Running;


        }
    private:
        int m_delay = 20;
    };



    class FindEnemyBoss1 : public BehaviorNodeDecorator<Boss1, IActionNode>
    {
    public:
        FindEnemyBoss1(ICompositeNode* parent) : BehaviorNodeDecorator<Boss1, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            
            if (!getGameObject()->findValidTarget())
            {
                
                return Failed;
            }

            
            return Success;
        }
    };
	class PlayerDictanceBoss1 : public BehaviorNodeDecorator<Boss1, IConditionalNode>
    {
    public:
        PlayerDictanceBoss1(ICompositeNode* node,float min, float max)
            : BehaviorNodeDecorator<Boss1, IConditionalNode>(node)
			,m_min(min)
			,m_max(max)

        {
        }

        bool condition()
        {
            float Distance = getGameObject()->getDistanceToPlayer().getLength();

            return Distance> m_min &&Distance< m_max;
        }
	private:
        float m_min;
        float m_max;
        
    };
    class IsDeadBoss1 : public BehaviorNodeDecorator<Boss1, IConditionalNode>
    {
    public:
        IsDeadBoss1(ICompositeNode* node)
            : BehaviorNodeDecorator<Boss1, IConditionalNode>(node)


        {
        }

        bool condition()
        {
            

            return getGameObject()->getHP()<=0;
        }
    private:



    };



}
