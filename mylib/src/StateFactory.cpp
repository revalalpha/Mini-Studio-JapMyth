#include "StateFactory.h"
#include "HeroState.h"

std::unique_ptr<State<Hero>> StateFactory::createState(const std::string& stateName, Hero* owner)
{
    if (stateName == "Idle") return std::make_unique<IdleState>(owner);
    if (stateName == "Run") return std::make_unique<RunState>(owner);
    if (stateName == "Attack") return std::make_unique<AttackState>(owner);
    if (stateName == "Shoot") return std::make_unique<ShootState>(owner);
    if (stateName == "Hurt") return std::make_unique<HurtState>(owner);
    if (stateName == "Death") return std::make_unique<DeathState>(owner);
    return nullptr;
}