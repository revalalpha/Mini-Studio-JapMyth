#pragma once

#include <memory>
#include <string>
#include "State.h"
#include "Hero.h"

class StateFactory
{
public:
    static std::unique_ptr<State<Hero>> createState(const std::string& stateName, Hero* owner);
};