#pragma once
#include <SFML/Graphics.hpp>

class Hero;

class IState
{
public:
	virtual ~IState() = default;
	virtual void handleInput(Hero& hero) = 0;
	virtual void update(Hero& hero, float deltaTime) = 0;
	virtual void setTexture(Hero& hero) = 0;
	virtual bool isTemporaryState() const;

protected:
	static bool isGoingLeft();
	static bool isGoingRight();
	static bool isJumping();
	static bool isDodging();
	static bool canDodge();
	static bool isAttacking();
	static bool isJumpAttacking();
	static bool isBlocking();

	static void updateDirection(Hero& hero);

	static bool m_dashAvailable;
	static sf::Clock m_dashCooldownClock;
	static const float m_dashCooldownDuration;

	static bool m_mouseLeftPressed;
};

class IdleState : public IState
{
public:
	void handleInput(Hero& hero) override;
	void update(Hero& hero, float deltaTime) override;
	void setTexture(Hero& hero) override;

protected:
	const int m_frameWidth = 96;
	const int m_frameHeight = 34;
	int m_frameCount = 10;
	int m_currentFrame = 0;
	float m_frameTime = 0.1f;
	sf::Clock m_elapsedTime;
};

class AttackState : public IState
{
public:
	void handleInput(Hero& hero) override;
	void update(Hero& hero, float deltaTime) override;
	void setTexture(Hero& hero) override;

protected:
	const int m_frameWidth = 96;
	const int m_frameHeight = 34;
	int m_frameCount = 7;
	int m_currentFrame = 0;
	float m_frameTime = 0.07f;
	sf::Clock m_elapsedTime;
};

class JumpState : public IState
{
public:
	void handleInput(Hero& hero) override;
	void update(Hero& hero, float deltaTime) override;
	void setTexture(Hero& hero) override;

protected:
	sf::Clock m_elapsedTime;
	const float m_frameTime = 0.2f;
	int m_currentFrame = 0;
	const int m_frameCount = 3;
	const int m_frameWidth = 96;
	const int m_frameHeight = 36;

	float m_gravity = 80.0f;
};

class JumpAttack : public IState
{
public:
	void handleInput(Hero& hero) override;
	void update(Hero& hero, float deltaTime) override;
	void setTexture(Hero& hero) override;

private:
	sf::Clock m_elapsedTime;
	const float m_frameTime = 0.07f;
	int m_currentFrame = 0;
	const int m_frameCount = 6;
	const int m_frameWidth = 96;
	const int m_frameHeight = 42;

	float m_gravity = 80.0f;
};

class BlockState : public IState
{
public:
	void handleInput(Hero& hero) override;
	void update(Hero& hero, float deltaTime) override;
	void setTexture(Hero& hero) override;

protected:
	sf::Clock m_elapsedTime;
	const float m_frameTime = 0.3f;
	int m_currentFrame = 0;
	const int m_frameCount = 2;
	const int m_frameWidth = 96;
	const int m_frameHeight = 34;
};

class RunState : public IState
{
public:
	void handleInput(Hero& hero) override;
	void update(Hero& hero, float deltaTime) override;
	void setTexture(Hero& hero) override;

protected:
	sf::Clock m_elapsedTime;
	const float m_frameTime = 0.03f;
	int m_currentFrame = 0;
	const int m_frameCount = 16;
	const int m_frameWidth = 96;
	const int m_frameHeight = 34;
};

class DodgeState : public IState
{
public:
	void handleInput(Hero& hero) override;
	void update(Hero& hero, float deltaTime) override;
	void setTexture(Hero& hero) override;
	bool isTemporaryState() const override { return true; }

protected:
	sf::Clock m_elapsedTime;
	const float m_frameTime = 0.08f;
	int m_currentFrame = 0;
	const int m_frameCount = 1;
	const int m_frameWidth = 70;
	const int m_frameHeight = 32;
	const float m_dodgeSpeed = 250.0f;
	const float m_dodgeDuration = 0.01f;
};

class HurtState : public IState
{
public:
	void handleInput(Hero& hero) override;
	void update(Hero& hero, float deltaTime) override;
	void setTexture(Hero& hero) override;

protected:
	sf::Clock m_elapsedTime;
	const float m_frameTime = 0.2f;
	int m_currentFrame = 0;
	const int m_frameCount = 4;
	const int m_frameWidth = 96;
	const int m_frameHeight = 34;
	const float m_hurtDuration = 0.5f;
	sf::Clock m_hurtTimer;

};

class DeathState : public IState
{
public:
	void handleInput(Hero& hero) override;
	void update(Hero& hero, float deltaTime) override;
	void setTexture(Hero& hero) override;

protected:
	sf::Clock m_elapsedTime;
	const float m_frameTime = 0.1f;
	int m_currentFrame = 0;
	const int m_frameCount = 9;
	const int m_frameWidth = 96;
	const int m_frameHeight = 34;

	bool m_animationComplete = false;
};