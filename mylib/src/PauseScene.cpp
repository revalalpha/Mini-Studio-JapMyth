
#include "PauseScene.h"

#include "game.h"

#include "SceneManager.h"

// PAUSE MENU
PauseScene::PauseScene(sf::RenderWindow* window, SceneManager* sceneManager, const float& framerate, const std::string& execPath)
    : IScene(window, framerate, execPath), m_sceneManager(sceneManager)
{
    setPauseText(window);

}

void PauseScene::setPauseText(sf::RenderWindow* window)
{
    // TITLE
    m_titleFont.loadFromFile(_m_textureCache.getAbsoluteFilepath("BreatheFireIi-2z9W.ttf"));
    m_text.setFont(m_titleFont);
    m_text.setString("R I S I N G");
    m_text.setCharacterSize(100);
    m_text.setFillColor(sf::Color(255, 215, 0));
    m_text.setStyle(sf::Text::Bold);
    m_text.setOutlineThickness(2);
    m_text.setOutlineColor(sf::Color::Black);

    sf::FloatRect textBounds = m_text.getLocalBounds();
    m_text.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
    m_text.setPosition(window->getSize().x / 2.f + 27, 200.f);

    // MENU
    std::vector<std::string> titles = { "R E S U M E", "E X I T" };

    m_font.loadFromFile(_m_textureCache.getAbsoluteFilepath("BreatheFireIi-2z9W.ttf"));

    float boxWidth = 350.f;
    float boxHeight = 80.f;
    float startX = (window->getSize().x - boxWidth) / 2.f + 10;
    float startY = 720.f;
    float spacing = 20.f;

    for (size_t i = 0; i < titles.size(); ++i)
    {
        sf::RectangleShape box(sf::Vector2f(boxWidth, boxHeight));
        box.setPosition(startX, startY + i * (boxHeight + spacing));
        m_menuBoxes.push_back(box);

        m_menuTitles.push_back(titles[i]);
    }
}



void PauseScene::processInput(const sf::Event& event)
{

    if (event.type == sf::Event::MouseMoved)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*m_renderWindow);

        for (size_t i = 0; i < m_menuBoxes.size(); ++i)
        {
            if (m_menuBoxes[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                m_selectedIndex = i;
        }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (m_selectedIndex < m_menuTitles.size())
        {
            const std::string& selectedOption = m_menuTitles[m_selectedIndex];

            if (selectedOption == "R E S U M E")
            {
                m_sceneManager->setCurrentScene(1);

            }
            else if (selectedOption == "E X I T")
                m_renderWindow->close();
        }
    }
}

void PauseScene::update(const float& deltaTime)
{

}

void PauseScene::render()
{
    m_renderWindow->draw(m_text);

    for (size_t i = 0; i < m_menuBoxes.size(); ++i)
    {


        m_renderWindow->draw(m_menuBoxes[i]);

        sf::Text text;
        text.setFont(m_font);
        text.setString(m_menuTitles[i]);
        text.setCharacterSize(36);
        text.setOutlineThickness(1);
        text.setOutlineColor(sf::Color::Black);

        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
        text.setPosition(m_menuBoxes[i].getPosition().x + m_menuBoxes[i].getSize().x / 2.f
            , m_menuBoxes[i].getPosition().y + m_menuBoxes[i].getSize().y / 2.5f);

        if (i == m_selectedIndex)
        {
            m_menuBoxes[i].setFillColor(sf::Color(0, 0, 0, 200));
            text.setFillColor(sf::Color::Yellow);
        }
        else
        {
            m_menuBoxes[i].setFillColor(sf::Color(0, 0, 0, 80));
            text.setFillColor(sf::Color(255, 215, 0));
        }

        m_renderWindow->draw(text);
    }
}