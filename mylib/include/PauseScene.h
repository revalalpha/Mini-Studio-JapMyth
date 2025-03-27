#pragma once

#include "IScene.h"

class SceneManager;

class PauseScene : public IScene
{
public:
    PauseScene(sf::RenderWindow* window, SceneManager* sceneManager, const float& framerate, const std::string& execPath);

    void processInput(const sf::Event& event) override;
    void update(const float& deltaTime) override;
    void setPauseText(sf::RenderWindow* window);
    void render() override;

private:
    std::vector<std::string> m_menuTitles;
    std::vector<sf::RectangleShape> m_menuBoxes;
    size_t m_selectedIndex = 0;
    SceneManager* m_sceneManager;
    sf::Text m_text;
    sf::Font m_font;
    sf::Font m_titleFont;
    sf::Text m_backPauseText;
    sf::RectangleShape m_pauseScreen;
    

};