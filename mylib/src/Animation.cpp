#include "Animation.h"

Animation::Animation()
    : m_sprite(nullptr), m_frameTime(0.1f), m_elapsedTime(0.f), m_currentFrame(0), m_loop(true), m_finished(false)
{}

Animation::Animation(sf::Sprite& sprite, const std::vector<sf::IntRect>& frames, float frameTime, bool loop)
    : m_sprite(&sprite), m_frames(frames), m_frameTime(frameTime), m_elapsedTime(0.f),
    m_currentFrame(0), m_loop(loop), m_finished(false)
{
    if (!m_frames.empty())
        m_sprite->setTextureRect(m_frames[0]);
}

void Animation::update(float deltaTime)
{
    if (m_finished || m_frames.empty()) 
        return;

    m_elapsedTime += deltaTime;

    if (m_elapsedTime >= m_frameTime) 
    {
        m_elapsedTime = 0.f;
        m_currentFrame++;

        if (m_currentFrame >= m_frames.size())
        {
            if (m_loop) 
            {
                m_currentFrame = 0;
            }
            else 
            {
                m_currentFrame = m_frames.size() - 1;
                m_finished = true;
            }
        }

        m_sprite->setTextureRect(m_frames[m_currentFrame]);
    }
}

void Animation::reset()
{
    m_currentFrame = 0;
    m_elapsedTime = 0.f;
    m_finished = false;
    if (!m_frames.empty())
        m_sprite->setTextureRect(m_frames[0]);
}

bool Animation::isFinished() const
{
    return m_finished;
}

void Animation::setFrames(const std::vector<sf::IntRect>& frames)
{
    m_frames = frames;
    reset();
}

void Animation::setLoop(bool loop)
{
    m_loop = loop;
}

void Animation::setFrameTime(float frameTime)
{
    m_frameTime = frameTime;
}