#pragma once

class IComponent
{
public:
    virtual ~IComponent() = default;
    virtual void update(float deltaTime) = 0;
};