#pragma once
#include <algorithm>

#include "IComponent.h"

class HealthComponent : public IComponent
{
public:
    HealthComponent(int maxHp) : m_hp(maxHp), m_maxHp(maxHp) {}

    void takeDamage(int damage)
	{
        if (!m_isInvulnerable) 
        {
            m_hp = std::max(0, m_hp - damage);
            m_isInvulnerable = true;
        }
    }

    bool isAlive() const
    {
	    return m_hp > 0;
    }

    void update(float deltaTime) override
	{
        if (m_isInvulnerable)
        {
            m_invulnTimer += deltaTime;
            if (m_invulnTimer >= m_invulnDuration) 
            {
                m_isInvulnerable = false;
                m_invulnTimer = 0.0f;
            }
        }
    }

private:
    int m_hp;
    int m_maxHp;
    bool m_isInvulnerable = false;
    float m_invulnTimer = 0.0f;
    float m_invulnDuration = 1.5f;
};
