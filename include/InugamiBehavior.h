#pragma once
#pragma once

#include "Tree.h"
#include "Inugami.h"




namespace BT
{

    class WaitInugami : public IActionNode
    {
    private:
        sf::Time m_duration;
        sf::Clock m_timer;
        bool m_started = false;

    public:
        WaitInugami(ICompositeNode* parent, float duration)
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

    class WalkInugami : public BehaviorNodeDecorator<Inugami, IActionNode>
    {
    public:
        WalkInugami(ICompositeNode* parent) : BehaviorNodeDecorator<Inugami, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            getGameObject()->setSpeed(500);
            getGameObject()->SpeedLimit = 100.f;
            return Success;
        }


    };

    class SprintInugami : public BehaviorNodeDecorator<Inugami, IActionNode>
    {
    public:
        SprintInugami(ICompositeNode* parent) : BehaviorNodeDecorator<Inugami, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            getGameObject()->setSpeed(1000);
            getGameObject()->SpeedLimit = 200.f;
            return Success;
        }


    };
    class IdleInugami : public BehaviorNodeDecorator<Inugami, IActionNode>
    {
    public:
        IdleInugami(ICompositeNode* parent) : BehaviorNodeDecorator<Inugami, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            getGameObject()->setSpeed(0);
            getGameObject()->SpeedLimit = 100.f;
            return Success;
        }


    };

    class IsPlayerDeadInugami : public BehaviorNodeDecorator<Inugami, IActionNode>
    {
    public:
        IsPlayerDeadInugami(ICompositeNode* parent) : BehaviorNodeDecorator<Inugami, IActionNode>(parent)
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







    class MeleeInugami : public BehaviorNodeDecorator<Inugami, IActionNode>
    {
    public:
        MeleeInugami(ICompositeNode* parent) : BehaviorNodeDecorator<Inugami, IActionNode>(parent)
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



    class FindEnemyInugami : public BehaviorNodeDecorator<Inugami, IActionNode>
    {
    public:
        FindEnemyInugami(ICompositeNode* parent) : BehaviorNodeDecorator<Inugami, IActionNode>(parent)
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
	class PlayerDictanceInugami : public BehaviorNodeDecorator<Inugami, IConditionalNode>
    {
    public:
        PlayerDictanceInugami(ICompositeNode* node,float min, float max)
            : BehaviorNodeDecorator<Inugami, IConditionalNode>(node)
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
    class IsDeadInugami : public BehaviorNodeDecorator<Inugami, IConditionalNode>
    {
    public:
        IsDeadInugami(ICompositeNode* node)
            : BehaviorNodeDecorator<Inugami, IConditionalNode>(node)


        {
        }

        bool condition()
        {
            

            return getGameObject()->getHP()<=0;
        }
    private:



    };



}
