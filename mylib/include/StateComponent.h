#pragma once
#include "IComponent.h"
#include "heroState.h"

class StateComponent : public IComponent
{
public:
    using StateName = HeroStateNames::StateName;

    void setState(StateName newState)
    {
	    m_currentState = newState;
    }
    StateName getCurrentState() const
    {
	    return m_currentState;
    }

    void update(float deltaTime) override {}

private:
    StateName m_currentState = StateName::Idle;
};
