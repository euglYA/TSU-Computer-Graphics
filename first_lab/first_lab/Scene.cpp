#include "Scene.h"

Scene::Scene() {
	window = new sf::RenderWindow(sf::VideoMode(800, 800), "spinning box", sf::Style::Default);
}

Scene::~Scene() {
	if (window)
		delete window;
}

bool Scene::isOpen() {
	return window->isOpen();
}

void Scene::render() {
	window->clear(sf::Color::White);

	for (int i = 0; i < objects.size(); i++)
		objects[i]->render(*window);

	window->display();
}

void Scene::addObject(Object* obj) {
	objects.push_back(obj);
}