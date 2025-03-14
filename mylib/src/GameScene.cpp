#include "GameScene.h"

GameScene::GameScene(sf::RenderWindow* window, SceneManager* sceneManager, const float& framerate, const std::string& execPath)
    : IScene(window, framerate, execPath), m_sceneManager(sceneManager)
{
    m_game = new Game(*m_renderWindow,execPath);
}

GameScene::~GameScene()
{

    delete m_game;
}
void GameScene::setBackground(sf::RenderWindow* window)
{
    m_background.loadFromFile(_m_textureCache.getAbsoluteFilepath("dungeon_background_5.png"));
    m_backgroundSprite.setTexture(m_background);
    m_backgroundSprite.setPosition(m_renderWindow->getPosition().x, m_renderWindow->getPosition().y);
    m_backgroundSprite.setScale(1.3, 1.1);
}
void GameScene::processInput(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            m_sceneManager->setCurrentScene(2);
        }
    }


    m_game->handleInputs(event);
}

void GameScene::update(const float& deltaTime)
{

    m_game->update(deltaTime);
}

void GameScene::render()
{

    //m_renderWindow->clear();


	m_game->render(*m_renderWindow);
    

    //m_game->renderBoundingBox(*m_renderWindow);
}