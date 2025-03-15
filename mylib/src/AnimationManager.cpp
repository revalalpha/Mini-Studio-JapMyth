#include "AnimationManager.h"

AnimationManager::AnimationManager(sf::Sprite& sprite)
    : m_sprite(sprite), m_currentAnimation(nullptr), m_currentAnimationName("")
{}

void AnimationManager::addAnimation(const std::string& name, const std::vector<sf::IntRect>& frames, float frameTime, bool loop)
{
    m_animations[name] = Animation(m_sprite, frames, frameTime, loop);
}

void AnimationManager::setAnimation(const std::string& name)
{
    if (m_animations.find(name) != m_animations.end()) 
    {
        if (m_currentAnimationName != name) 
        {
            m_currentAnimation = &m_animations[name];
            m_currentAnimation->reset();
            m_currentAnimationName = name;
        }
    }
}

void AnimationManager::update(float deltaTime) const
{
    if (m_currentAnimation)
        m_currentAnimation->update(deltaTime);
}

bool AnimationManager::isAnimationFinished() const
{
    return m_currentAnimation && m_currentAnimation->isFinished();
}

std::string AnimationManager::getCurrentAnimation() const
{
    return m_currentAnimationName;
}
