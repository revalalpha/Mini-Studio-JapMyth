#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include <functional>
#include "State.h"

class Hero;

class StateManager
{
public:
    StateManager(Hero* owner)
        : m_owner(owner), m_currentState(nullptr)
    {}

    void registerState(const std::string& stateName, std::function<std::unique_ptr<State<Hero>>(Hero*)> constructor)
    {
        m_stateConstructors[stateName] = constructor;
    }

    void changeState(const std::string& stateName)
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


    void update(float deltaTime)
    {
        if (m_currentState)
            m_currentState->update(*m_owner, deltaTime);
    }

    void handleInput()
    {
        if (m_currentState)
            m_currentState->handleInput(*m_owner);
    }

private:
    Hero* m_owner;
    State<Hero>* m_currentState;
    std::unordered_map<std::string, std::unique_ptr<State<Hero>>> m_stateMap;
    std::unordered_map<std::string, std::function<std::unique_ptr<State<Hero>>(Hero*)>> m_stateConstructors;
};
