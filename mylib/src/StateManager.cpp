#include "StateManager.h"

StateManager::StateManager(Hero* owner)
    : m_owner(owner), m_currentState(nullptr)
{}

void StateManager::registerState(const std::string& stateName,
	std::function<std::unique_ptr<State<Hero>>(Hero*)> constructor)
{
	m_stateConstructors[stateName] = constructor;
}

void StateManager::changeState(const std::string& stateName)
{
	if (m_currentState)
	{
		m_currentState->exit(*m_owner);
	}

	auto it = m_stateConstructors.find(stateName);
	if (it != m_stateConstructors.end())
	{
		m_currentState = it->second(m_owner).get();
		m_stateMap[stateName] = std::move(it->second(m_owner));
		m_currentState->enter(*m_owner);
	}
}

void StateManager::update(float deltaTime)
{
	if (m_currentState)
		m_currentState->update(*m_owner, deltaTime);
}

void StateManager::handleInput()
{
	if (m_currentState)
		m_currentState->handleInput(*m_owner);
}

