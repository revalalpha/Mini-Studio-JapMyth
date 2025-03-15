#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SFML/Graphics.hpp>

class Animation {
public:
    Animation();
    Animation(sf::Sprite& sprite, const std::vector<sf::IntRect>& frames, float frameTime, bool loop = true);

    void update(float deltaTime);
    void reset();
    bool isFinished() const;

    void setFrames(const std::vector<sf::IntRect>& frames);
    void setLoop(bool loop);
    void setFrameTime(float frameTime);

private:
    sf::Sprite* m_sprite;
    std::vector<sf::IntRect> m_frames;
    float m_frameTime;
    float m_elapsedTime;
    std::size_t m_currentFrame;
    bool m_loop;
    bool m_finished;
};

#endif // ANIMATION_H
