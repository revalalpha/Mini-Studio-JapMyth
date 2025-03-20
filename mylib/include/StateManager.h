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
    StateManager(Hero* owner);

    void registerState(const std::string& stateName, std::function<std::unique_ptr<State<Hero>>(Hero*)> constructor);
    void changeState(const std::string& stateName);
    void update(float deltaTime);
    void handleInput();

private:
    Hero* m_owner;
    State<Hero>* m_currentState;
    std::unordered_map<std::string, std::unique_ptr<State<Hero>>> m_stateMap;
    std::unordered_map<std::string, std::function<std::unique_ptr<State<Hero>>(Hero*)>> m_stateConstructors;
};
