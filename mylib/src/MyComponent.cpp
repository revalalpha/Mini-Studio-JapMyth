#include "MyComponent.h"

ComponentGameObject::ComponentGameObject(const std::string& name)
	: GameObject(name)
{
}

void ComponentGameObject::processInput(const sf::Event& event)
{
	for (auto& component : m_components)
		component.second->processInput(event);

	GameObject::processInput(event);
}

void ComponentGameObject::update(const float& deltaTime)
{
	for (auto& component : m_components)
		component.second->update(deltaTime);

	GameObject::update(deltaTime);
}

void ComponentGameObject::render(sf::RenderWindow& window)
{
	for (auto& component : m_components)
		component.second->render(window);

	GameObject::render(window);
}

void ComponentGameObject::addComposite(std::shared_ptr<Composite> component)
{
	component->setOwner(this);
	component->initialize();
	m_components[component->getName()] = component;
}

Composite* ComponentGameObject::getComposite(const std::string& name)
{
	auto it = m_components.find(name);
	if (it != m_components.end())
		return it->second.get();

	return nullptr;
}

void ComponentGameObject::removeComposite(const std::string& name)
{
	auto it = m_components.find(name);
	if (it != m_components.end())
		m_components.erase(it);
}

ComponentScene::ComponentScene(sf::RenderWindow* window, const float& framerate, const std::string& name)
	: SceneBase(window, framerate, name)
{
}

void ComponentScene::processInput(const sf::Event& event)
{
	for (auto& child : m_children)
		child->processInput(event);
}

void ComponentScene::update(const float& deltaTime)
{
	for (auto& child : m_children)
		child->update(deltaTime);
}

void ComponentScene::render()
{
	for (auto& child : m_children)
		child->render();
}