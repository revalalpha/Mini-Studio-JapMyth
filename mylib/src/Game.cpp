#include "Game.h"
#include "Scrolling.h"
#include "Enemy.h"
#include "TextureManager.h"

Game::Game(sf::RenderWindow* window, const float& framerate)
    : SceneBase(window, framerate)
{
    initialize();
}

void Game::setPlayer()
{
    TextureManager::getInstance().initialize();
    m_player = std::make_shared<Hero>("Player");

    m_player->getSprite().setPosition(500, 500);

    m_player->setState(stateName::idle);

    auto cameraTarget = std::make_shared<CameraTarget>(1.0f, true);
    m_player->addComponent(cameraTarget);
    m_gameObjects.push_back(m_player);
}

void Game::setEnemy()
{
}

void Game::initialize()
{
    Camera::getInstance().initialize(m_renderWindow);
    Camera::getInstance().setZoom(1.f);
    Camera::getInstance().setInterpolationSpeed(4.0f);

    setPlayer();
    /*setEnemy();*/
}

void Game::processInput(const sf::Event& event)
{
    m_player->processInput(event);
    m_player->handleInput();

    SceneBase::processInput(event);
}

void Game::update(const float& deltaTime)
{
    SceneBase::update(deltaTime);

    for (auto& gameObject : m_gameObjects)
        gameObject->update(deltaTime);

    m_player->update(deltaTime);

    auto playerRender = static_cast<SquareRenderer*>(m_player->getComposite("SquareRenderer"));
    if (playerRender)
    {
        sf::Vector2f playerPos = playerRender->getPosition();
        /*IEnemy::updateAllEnemyLOS(m_gameObjects, playerPos);*/
    }

    Camera::getInstance().update(deltaTime);
}

void Game::render()
{
    Camera::getInstance().apply();

    for (auto& gameObject : m_gameObjects)
        gameObject->render(*m_renderWindow);

    m_renderWindow->draw(m_player->getSprite());

    SceneBase::render();
}
