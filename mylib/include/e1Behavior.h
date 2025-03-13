#pragma once

#include "behaviorTree.h"
#include "ennemie.h"

class Game;

namespace BT
{
    class PatrolAction : public IActionNode
    {
    public:
        PatrolAction(ICompositeNode* parent) : IActionNode(parent) {}

        Status tick() override
        {
            std::cout << "Patrolling..." << std::endl;
            return Success;
        }
    };

    class ChaseAction : public IActionNode
    {
    public:
        ChaseAction(ICompositeNode* parent) : IActionNode(parent) {}

        Status tick() override
        {
            std::cout << "Chasing player..." << std::endl;
            return Success;
        }
    };

    class AttackAction : public IActionNode
    {
    public:
        AttackAction(ICompositeNode* parent) : IActionNode(parent) {}

        Status tick() override
        {
            std::cout << "Attacking player!" << std::endl;
            return Success;
        }
    };

}