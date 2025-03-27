#pragma once
#pragma once

#include "Tree.h"
#include "Kappa.h"




namespace BT
{

    class WaitKappa : public IActionNode
    {
    private:
        sf::Time m_duration;
        sf::Clock m_timer;
        bool m_started = false;

    public:
        WaitKappa(ICompositeNode* parent, float duration)
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

    class WalkKappa : public BehaviorNodeDecorator<Kappa, IActionNode>
    {
    public:
        WalkKappa(ICompositeNode* parent) : BehaviorNodeDecorator<Kappa, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            getGameObject()->setSpeed(500);
            getGameObject()->SpeedLimit = 50.f;
            return Success;
        }


    };

    class OppositeWalkKappa : public BehaviorNodeDecorator<Kappa, IActionNode>
    {
    public:
        OppositeWalkKappa(ICompositeNode* parent) : BehaviorNodeDecorator<Kappa, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            getGameObject()->setSpeed(-500);
            getGameObject()->SpeedLimit = 200.f;
            return Success;
        }


    };

    class SprintKappa : public BehaviorNodeDecorator<Kappa, IActionNode>
    {
    public:
        SprintKappa(ICompositeNode* parent) : BehaviorNodeDecorator<Kappa, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            getGameObject()->setSpeed(1000);
            getGameObject()->SpeedLimit = 200.f;
            return Success;
        }


    };
    class IdleKappa : public BehaviorNodeDecorator<Kappa, IActionNode>
    {
    public:
        IdleKappa(ICompositeNode* parent) : BehaviorNodeDecorator<Kappa, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            getGameObject()->setSpeed(0);
            getGameObject()->SpeedLimit = 100.f;
            return Success;
        }


    };

    class IsPlayerDeadKappa : public BehaviorNodeDecorator<Kappa, IActionNode>
    {
    public:
        IsPlayerDeadKappa(ICompositeNode* parent) : BehaviorNodeDecorator<Kappa, IActionNode>(parent)
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




    class FireKappa : public BehaviorNodeDecorator<Kappa, IActionNode>
    {
    public:
        FireKappa(ICompositeNode* parent) : BehaviorNodeDecorator<Kappa, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            if (!getGameObject()->isCurrentTargetValid())
                return Failed;

            if (m_delay == 0)
            {
                getGameObject()->fireWithPistol();
                m_delay = 10;
                return Success;
            }
            m_delay--;
            return Running;


        }
    private:
        int m_delay = 10;
    };





    class FindEnemyKappa : public BehaviorNodeDecorator<Kappa, IActionNode>
    {
    public:
        FindEnemyKappa(ICompositeNode* parent) : BehaviorNodeDecorator<Kappa, IActionNode>(parent)
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
	class PlayerDictanceKappa : public BehaviorNodeDecorator<Kappa, IConditionalNode>
    {
    public:
        PlayerDictanceKappa(ICompositeNode* node,float min, float max)
            : BehaviorNodeDecorator<Kappa, IConditionalNode>(node)
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
    class IsDeadKappa : public BehaviorNodeDecorator<Kappa, IConditionalNode>
    {
    public:
        IsDeadKappa(ICompositeNode* node)
            : BehaviorNodeDecorator<Kappa, IConditionalNode>(node)


        {
        }

        bool condition()
        {
            

            return getGameObject()->getHP()<=0;
        }
    private:



    };



}
