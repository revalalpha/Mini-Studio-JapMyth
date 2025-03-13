#include "IScene.h"

IScene::IScene(sf::RenderWindow* window, const float& framerate, const std::string& execPath)
    : m_renderWindow(window)
    , m_refreshTime(sf::seconds(1.f / framerate))
	,_m_textureCache(execPath)
{

}

sf::Time IScene::getRefreshTime() const
{
    return m_refreshTime;
}