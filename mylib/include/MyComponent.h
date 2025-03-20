#pragma once
#include <unordered_map>

#include "MyComposite.h"
#include "GameObject.h"
#include "SceneBase.h"

class ComponentGameObject : public GameObject
{
public:
	ComponentGameObject(const std::string& name = "ComponentGameObject");
	virtual ~ComponentGameObject() = default;

	void processInput(const sf::Event& event) override;
	void update(const float& deltaTime) override;
	void render(sf::RenderWindow& window) override;

	void addComposite(std::shared_ptr<Composite> component);
	Composite* getComposite(const std::string& name);
	void removeComposite(const std::string& name);

private:
	std::unordered_map<std::string, std::shared_ptr<Composite>> m_components;
};

class ComponentScene : public SceneBase
{
public:
	ComponentScene(sf::RenderWindow* window, const float& framerate, const std::string& name = "ComponentScene");
	~ComponentScene() = default;

	void processInput(const sf::Event& event) override;
	void update(const float& deltaTime) override;
	void render() override;
};