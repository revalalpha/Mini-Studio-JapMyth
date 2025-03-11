#include "heroState.h"
#include "hero.h"

HeroState::HeroState() : m_currentState(nullptr), m_currentStateName(StateEnum::idle)
{
    m_states[StateEnum::idle] = std::make_shared<IdleState>();
    m_states[StateEnum::run] = std::make_shared<RunState>();
    m_states[StateEnum::jump] = std::make_shared<JumpState>();
    m_states[StateEnum::attack] = std::make_shared<AttackState>();
    m_states[StateEnum::dodge] = std::make_shared<DodgeState>();
    m_states[StateEnum::jump_attack] = std::make_shared<JumpAttack>();
    m_states[StateEnum::block] = std::make_shared<BlockState>();
    m_states[StateEnum::hurt] = std::make_shared<HurtState>();
    m_states[StateEnum::death] = std::make_shared<DeathState>();

    m_currentState = m_states[StateEnum::idle];
}

HeroState::~HeroState()
{
    m_states.clear();
    m_currentState = nullptr;

    while (!m_stateStack.empty())
    {
        m_stateStack.pop();
    }
}

void HeroState::setState(Hero* hero, HeroStateNames::stateName newState)
{
    if (newState == StateEnum::death)
    {
        while (!m_stateStack.empty())
        {
            m_stateStack.pop();
        }
    }

    if (m_states.find(newState) == m_states.end())
        return;

    m_currentState = m_states[newState];
    m_currentStateName = newState;

    if (hero != nullptr)
        m_currentState->setTexture(*hero);
}

void HeroState::pushState(Hero* hero, HeroStateNames::stateName newState)
{
    if (m_states.find(newState) == m_states.end())
        return;

    m_stateStack.push(std::make_pair(m_currentStateName, m_currentState));

    m_currentState = m_states[newState];
    m_currentStateName = newState;

    if (hero != nullptr)
        m_currentState->setTexture(*hero);
}

void HeroState::popState(Hero* hero)
{
    if (m_stateStack.empty())
        return;

    auto previousState = m_stateStack.top();
    m_stateStack.pop();

    m_currentState = previousState.second;
    m_currentStateName = previousState.first;

    if (hero != nullptr)
        m_currentState->setTexture(*hero);
}

std::shared_ptr<IState> HeroState::getCurrentState() const
{
    return m_currentState;
}

HeroStateNames::stateName HeroState::getCurrentStateName() const
{
    return m_currentStateName;
}

void HeroState::handleInput(Hero& hero)
{
    if (m_currentState != nullptr)
        m_currentState->handleInput(hero);
}

void HeroState::update(Hero& hero, float deltaTime)
{
    if (m_currentState != nullptr)
        m_currentState->update(hero, deltaTime);
}