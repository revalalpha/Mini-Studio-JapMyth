#include "Game.h"
#include "Scrolling.h"
#include "Enemy.h"
#include "TextureManager.h"
#include <iostream>

Game::Game(sf::RenderWindow* window, const float& framerate, TextureCache* texture)
    : SceneBase(window, framerate, texture)
{
    initialize();
}

void Game::setPlayer()
{
    m_player = std::make_shared<Hero>("Player");

    m_player->getSprite().setPosition(500, 500);

    m_player->setState(stateName::idle);

    auto cameraTarget = std::make_shared<CameraTarget>(1.0f, true);
    m_player->addComponent(cameraTarget);
    m_gameObjects.push_back(m_player);
}

//void Game::setPlayer()
//{
//    std::string heroTexture = "Hero"; // Nom exact donné dans loadTexture()
//
//    if (!TextureManager::getInstance().hasTexture(heroTexture))
//    {
//        std::cerr << "Erreur : La texture '" << heroTexture << "' n'a pas été chargée avant la création du joueur !" << std::endl;
//    }
//}

void Game::setEnemy()
{
}

void Game::initialize()
{
    sf::Texture& mapTexture = m_texture_cache->GetTexture("map\\Map.png");
	m_mapSprite.setTexture(mapTexture);
	m_mapSprite.setPosition(0, 0);
    setPlayer();

    Camera::getInstance().initialize(m_renderWindow);
    Camera::getInstance().setZoom(1.f);
    Camera::getInstance().setInterpolationSpeed(4.0f);
}


void Game::processInput(const sf::Event& event)
{
    m_player->processInput(event);
    m_player->handleInputs(event);

    SceneBase::processInput(event);
}

void Game::update(const float& deltaTime)
{
    SceneBase::update(deltaTime);

    for (auto& gameObject : m_gameObjects)
        gameObject->update(deltaTime);

    m_player->update(deltaTime);

    SquareRenderer* playerRender = nullptr;

    playerRender = dynamic_cast<SquareRenderer*>(m_player->getComponent("SquareRenderer"));
    if (playerRender) {
        sf::Vector2f playerPos = playerRender->getPosition();
        /*IEnemy::updateAllEnemyLOS(m_gameObjects, playerPos);*/
    }

    Camera::getInstance().update(deltaTime);
}

void Game::render()
{
    Camera::getInstance().apply();

    m_renderWindow->draw(m_mapSprite);

    for (auto& gameObject : m_gameObjects)
        gameObject->render(*m_renderWindow);

    m_renderWindow->draw(m_player->getSprite());

    SceneBase::render();
}
