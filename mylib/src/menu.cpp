//#include "menu.h"
//#include "game.h"
//#include "resourceManager.h"
//#include "SceneManager.h"
//
//// START MENU
//Menu::Menu(sf::RenderWindow* window, SceneManager* sceneManager, const float& framerate)
//    : SceneBase(window, framerate), m_sceneManager(sceneManager)
//{
//    setStartText(window);
//    setBackground(window);
//    playAudio(window);
//}
//
//void Menu::setStartText(sf::RenderWindow* window)
//{
//    // TITLE
//    m_titleFont.loadFromFile(PathManager::getResourcePath("BreatheFireIi-2z9W.ttf"));
//    m_gameTitle.setFont(m_titleFont);
//    m_gameTitle.setString("R I S I N G");
//    m_gameTitle.setCharacterSize(100);
//    m_gameTitle.setFillColor(sf::Color(255, 215, 0));
//    m_gameTitle.setStyle(sf::Text::Bold);
//    m_gameTitle.setOutlineThickness(2);
//    m_gameTitle.setOutlineColor(sf::Color::Black);
//
//    sf::FloatRect textBounds = m_gameTitle.getLocalBounds();
//    m_gameTitle.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
//    m_gameTitle.setPosition(window->getSize().x / 2.f + 27, 200.f);
//
//    // MENU
//    std::vector<std::string> titles = { "P L A Y", "E X I T" };
//
//    m_font.loadFromFile(PathManager::getResourcePath("BreatheFireIi-2z9W.ttf"));
//
//    float boxWidth = 350.f;
//    float boxHeight = 80.f;
//    float startX = (window->getSize().x - boxWidth) / 2.f + 10;
//    float startY = 720.f;
//    float spacing = 20.f;
//
//    for (size_t i = 0; i < titles.size(); ++i)
//    {
//        sf::RectangleShape box(sf::Vector2f(boxWidth, boxHeight));
//        box.setPosition(startX, startY + i * (boxHeight + spacing));
//        m_menuBoxes.push_back(box);
//
//        m_menuTitles.push_back(titles[i]);
//    }
//}
//
//void Menu::setBackground(sf::RenderWindow* window)
//{
//    m_background.loadFromFile(PathManager::getResourcePath("dungeon_background_5.png"));
//    m_backgroundSprite.setTexture(m_background);
//    m_backgroundSprite.setPosition(m_renderWindow->getPosition().x, m_renderWindow->getPosition().y);
//    m_backgroundSprite.setScale(1.3, 1.1);
//}
//
//void Menu::playAudio(sf::RenderWindow* window)
//{
//    m_music.openFromFile(PathManager::getResourcePath("dungeonRising.mp3"));
//    m_music.play();
//    m_music.setVolume(50);
//    m_music.setLoop(true);
//}
//
//void Menu::processInput(const sf::Event& event)
//{
//    if (event.type == sf::Event::MouseMoved)
//    {
//        sf::Vector2i mousePos = sf::Mouse::getPosition(*m_renderWindow);
//
//        for (size_t i = 0; i < m_menuBoxes.size(); ++i)
//        {
//            if (m_menuBoxes[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
//                m_selectedIndex = i;
//        }
//    }
//
//    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
//    {
//        if (m_selectedIndex < m_menuTitles.size())
//        {
//            const std::string& selectedOption = m_menuTitles[m_selectedIndex];
//
//            if (selectedOption == "P L A Y")
//            {
//                m_sceneManager->setCurrentScene(1);
//                Game* gameScene = dynamic_cast<Game*>(m_sceneManager->getCurrentScene());
//                //if (gameScene)
//                //{
//                //    gameScene->setAudio();
//                //}
//                //m_music.stop();
//            }
//            else if (selectedOption == "E X I T")
//                m_renderWindow->close();
//        }
//    }
//}
//
//void Menu::update(const float& deltaTime)
//{
//
//}
//
//void Menu::render()
//{
//    m_renderWindow->draw(m_backgroundSprite);
//    m_renderWindow->draw(m_gameTitle);
//
//    for (size_t i = 0; i < m_menuBoxes.size(); ++i)
//    {
//
//
//        m_renderWindow->draw(m_menuBoxes[i]);
//
//        sf::Text text;
//        text.setFont(m_font);
//        text.setString(m_menuTitles[i]);
//        text.setCharacterSize(36);
//        text.setOutlineThickness(1);
//        text.setOutlineColor(sf::Color::Black);
//
//        sf::FloatRect textBounds = text.getLocalBounds();
//        text.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
//        text.setPosition(m_menuBoxes[i].getPosition().x + m_menuBoxes[i].getSize().x / 2.f
//            , m_menuBoxes[i].getPosition().y + m_menuBoxes[i].getSize().y / 2.5f);
//
//        if (i == m_selectedIndex)
//        {
//            m_menuBoxes[i].setFillColor(sf::Color(0, 0, 0, 200));
//            text.setFillColor(sf::Color::Yellow);
//        }
//        else
//        {
//            m_menuBoxes[i].setFillColor(sf::Color(0, 0, 0, 80));
//            text.setFillColor(sf::Color(255, 215, 0));
//        }
//
//        m_renderWindow->draw(text);
//    }
//}