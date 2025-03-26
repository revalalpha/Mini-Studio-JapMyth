#pragma once
#pragma once

#include "Tree.h"
#include "Inugami.h"




namespace BT
{

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

    class Walk : public BehaviorNodeDecorator<Inugami, IActionNode>
    {
    public:
        Walk(ICompositeNode* parent) : BehaviorNodeDecorator<Inugami, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            getGameObject()->setSpeed(500);
            getGameObject()->SpeedLimit = 100.f;
            return Success;
        }


    };

    class Sprint : public BehaviorNodeDecorator<Inugami, IActionNode>
    {
    public:
        Sprint(ICompositeNode* parent) : BehaviorNodeDecorator<Inugami, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            getGameObject()->setSpeed(1000);
            getGameObject()->SpeedLimit = 200.f;
            return Success;
        }


    };
    class Idle : public BehaviorNodeDecorator<Inugami, IActionNode>
    {
    public:
        Idle(ICompositeNode* parent) : BehaviorNodeDecorator<Inugami, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            getGameObject()->setSpeed(0);
            getGameObject()->SpeedLimit = 100.f;
            return Success;
        }


    };

    class IsPlayerDead : public BehaviorNodeDecorator<Inugami, IActionNode>
    {
    public:
        IsPlayerDead(ICompositeNode* parent) : BehaviorNodeDecorator<Inugami, IActionNode>(parent)
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




    class FirePistol : public BehaviorNodeDecorator<Inugami, IActionNode>
    {
    public:
        FirePistol(ICompositeNode* parent) : BehaviorNodeDecorator<Inugami, IActionNode>(parent)
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



    class Melee : public BehaviorNodeDecorator<Inugami, IActionNode>
    {
    public:
        Melee(ICompositeNode* parent) : BehaviorNodeDecorator<Inugami, IActionNode>(parent)
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



    class FindEnemy : public BehaviorNodeDecorator<Inugami, IActionNode>
    {
    public:
        FindEnemy(ICompositeNode* parent) : BehaviorNodeDecorator<Inugami, IActionNode>(parent)
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
	class PlayerDictance : public BehaviorNodeDecorator<Inugami, IConditionalNode>
    {
    public:
        PlayerDictance(ICompositeNode* node,float min, float max)
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
    class IsDead : public BehaviorNodeDecorator<Inugami, IConditionalNode>
    {
    public:
        IsDead(ICompositeNode* node)
            : BehaviorNodeDecorator<Inugami, IConditionalNode>(node)


        {
        }

        bool condition()
        {
            

            return getGameObject()->getHP()<=0;
        }
    private:



    };
    class SecondPhase : public BehaviorNodeDecorator<Inugami, IConditionalNode>
    {
    public:
        SecondPhase(ICompositeNode* node)
            : BehaviorNodeDecorator<Inugami, IConditionalNode>(node)
        {
        }

        bool condition()
        {

            return getGameObject()->getHP() <= getGameObject()->getMaxHP() / 2;
        }


    };


}
