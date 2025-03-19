//#pragma once
//
//#include "Tree.h"
//#include "Ennemy.h"
//
//class IEnemy;
//
//namespace BT
//{
//    namespace SamuraiBT
//    {
//        class MoveTowardsPlayer : public BehaviorNodeDecorator<IEnemy, IActionNode>
//        {
//        public:
//            MoveTowardsPlayer(ICompositeNode* parent) : BehaviorNodeDecorator(parent) {}
//
//            Status tick() override
//            {
//                sf::Vector2f enemyPosition = getGameObject()->getPosition();
//                sf::Vector2f playerPosition = getGameObject()->getPlayerPosition();
//                sf::Vector2f direction = playerPosition - enemyPosition;
//                float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
//
//                if (distance > 10.0f)
//                {
//                    direction /= distance;
//                    getGameObject()->setPosition(enemyPosition + direction * getGameObject()->getSpeed());
//                    return Running;
//                }
//                return Success;
//            }
//        };
//
//        class Attack : public BehaviorNodeDecorator<IEnemy, IActionNode>
//        {
//        public:
//            Attack(ICompositeNode* parent) : BehaviorNodeDecorator(parent) {}
//
//            Status tick() override
//            {
//                if (!getGameObject()->isCurrentTargetValid())
//                    return Failed;
//
//                float distance = getGameObject()->getDistanceToPlayer().getLength();
//
//                if (distance <= 50.0f)
//                {
//                    getGameObject()->performAttack();
//                    return Success;
//                }
//
//                return Failed;
//            }
//        };
//
//        class MoveAndAttackSequence : public BehaviorNodeDecorator<IEnemy, IActionNode>
//        {
//        public:
//            MoveAndAttackSequence(ICompositeNode* parent, const sf::Vector2f& position)
//                : BehaviorNodeDecorator(parent), m_moveTowardsPlayerNode(parent), m_attackNode(parent), m_position(position)
//            {
//            }
//
//            Status tick() override
//            {
//                if (m_moveTowardsPlayerNode.tick() == Success)
//                    return m_attackNode.tick();
//                return Running;
//            }
//
//        private:
//            MoveTowardsPlayer m_moveTowardsPlayerNode;
//            Attack m_attackNode;
//            sf::Vector2f m_position;
//        };
//    }
//
//    namespace KappaBT
//    {
//        class MoveToPosition : public BehaviorNodeDecorator<IEnemy, IActionNode>
//        {
//        public:
//            MoveToPosition(ICompositeNode* parent, const sf::Vector2f& position)
//                : BehaviorNodeDecorator(parent), m_targetPosition(position)
//            {
//            }
//
//            Status tick() override
//            {
//                sf::Vector2f enemyPosition = getGameObject()->getPosition();
//                sf::Vector2f direction = m_targetPosition - enemyPosition;
//                float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
//
//                if (distance > 10.0f)
//                {
//                    direction /= distance;
//                    getGameObject()->setPosition(enemyPosition + direction * getGameObject()->getSpeed());
//                    return Running;
//                }
//                return Success;
//            }
//
//        private:
//            sf::Vector2f m_targetPosition;
//        };
//
//        class FireProjectile : public BehaviorNodeDecorator<IEnemy, IActionNode>
//        {
//        public:
//            FireProjectile(ICompositeNode* parent) : BehaviorNodeDecorator(parent) {}
//
//            Status tick() override
//            {
//                if (!getGameObject()->isCurrentTargetValid())
//                    return Failed;
//
//                float distance = getGameObject()->getDistanceToPlayer().getLength();
//
//                if (distance <= 100.0f)
//                {
//                    getGameObject()->fireProjectile();
//                    return Success;
//                }
//
//                return Failed;
//            }
//        };
//
//        class MoveAndShootSequence : public BehaviorNodeDecorator<IEnemy, IActionNode>
//        {
//        public:
//            MoveAndShootSequence(ICompositeNode* parent, const sf::Vector2f& position)
//                : BehaviorNodeDecorator(parent), m_moveToPositionNode(parent, position), m_fireProjectileNode(parent)
//            {
//            }
//
//            Status tick() override
//            {
//                if (m_moveToPositionNode.tick() == Success)
//                    return m_fireProjectileNode.tick();
//                return Running;
//            }
//
//        private:
//            MoveToPosition m_moveToPositionNode;
//            FireProjectile m_fireProjectileNode;
//        };
//    }
//}