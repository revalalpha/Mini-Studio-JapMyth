#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include "Animation.h"
#include <unordered_map>
#include <string>

class AnimationManager {
public:
    AnimationManager(sf::Sprite& sprite);

    void addAnimation(const std::string& name, const std::vector<sf::IntRect>& frames, float frameTime, bool loop = true);
    void setAnimation(const std::string& name);
    void update(float deltaTime) const;

    bool isAnimationFinished() const;
    std::string getCurrentAnimation() const;

private:
    sf::Sprite& m_sprite;
    std::unordered_map<std::string, Animation> m_animations;
    Animation* m_currentAnimation;
    std::string m_currentAnimationName;
};

#endif // ANIMATION_MANAGER_H
