#pragma once
#include "IComponent.h"
#include "MyMath.h"

class MovementComponent : public IComponent
{
public:
    MovementComponent(float speed) : m_speed(speed)
	{}

    void move(const Vec2& direction, float deltaTime)
	{
        m_velocity.x = direction.x * m_speed * deltaTime;
        m_velocity.y = direction.y * m_speed * deltaTime;
    }

    void update(float deltaTime) override
	{
        m_position.x += m_velocity.x;
        m_position.y += m_velocity.y;
    }

    Vec2 getPosition() const
    {
	    return m_position;
    }

private:
    Vec2 m_position;
    Vec2 m_velocity;
    float m_speed;
};
