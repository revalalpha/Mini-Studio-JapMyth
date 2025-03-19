#pragma once

template <typename T>
class State
{
public:
    virtual ~State() = default;

    virtual void handleInput(T& owner) = 0;
    virtual void update(T& owner, float deltaTime) = 0;
    virtual void enter(T& owner) {}
    virtual void exit(T& owner) {}
};
