#pragma once
#include <SFML/Graphics.hpp>

class IGameObject
{
public:
    IGameObject() = default;
    virtual ~IGameObject() = default;

    // Pure virtual methods (state checks)
    virtual bool isAlive() = 0;            // Check if the object is alive
    virtual bool isShooting() = 0;         // Check if the object is shooting
    virtual bool isAttacking() = 0;        // Check if the object is attacking
    virtual bool isInvulnerable() = 0;     // Check if the object is invulnerable

    // Health and Shield Management
    virtual int getHp() = 0;               // Return health points
    virtual void takeDamage(int damage) = 0;     // Handle damage received
    virtual void setInvulnerable(float duration) = 0; // Set invulnerability duration
};