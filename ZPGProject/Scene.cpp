#include "Scene.h"

Scene::Scene(std::vector<std::shared_ptr<DrawableObject>> meshes)
{
	this->objects = std::move(meshes);
	EventNotifier::getInstance().subscribeKey(this);
}

Scene::Scene()
{
	this->objects = std::vector<std::shared_ptr<DrawableObject>>();
	EventNotifier::getInstance().subscribeKey(this);
}

Scene::~Scene()
{
	objects.erase(objects.begin(), objects.end());
}

void Scene::addDrawableObject(std::shared_ptr<DrawableObject> object)
{
	objects.push_back(object);
}

void Scene::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (auto& object : objects)
	{
		object->draw();
	}
}

void Scene::onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key) {
	case GLFW_KEY_RIGHT_BRACKET:
		if (action == GLFW_PRESS) {
			if (selectedObjectIndex < objects.size() - 1)
				selectedObjectIndex++;
			else
				selectedObjectIndex = 0;
		}
		break;

	case GLFW_KEY_UP:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(std::make_shared<TranslateTransform>(glm::vec3{ 0, .01f, 0 }));
		break;

	case GLFW_KEY_DOWN:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(std::make_shared<TranslateTransform>(glm::vec3{ 0, -.01f, 0 }));
		break;

	case GLFW_KEY_LEFT:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(std::make_shared<TranslateTransform>(glm::vec3{ -.01f, 0, 0 }));
		break;

	case GLFW_KEY_RIGHT:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(std::make_shared<TranslateTransform>(glm::vec3{ .01f, 0, 0 }));
		break;

	case GLFW_KEY_O:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(std::make_shared<RotationTransform>(-.05f, glm::vec3{ 0, 1, 0 }));
		break;

	case GLFW_KEY_LEFT_BRACKET:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(std::make_shared<RotationTransform>(.05f, glm::vec3{ 0, 1, 0 }));
		break;

	case GLFW_KEY_P:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(std::make_shared<RotationTransform>(-.05f, glm::vec3{ 1, 0, 0 }));
		break;

	case GLFW_KEY_SEMICOLON:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(std::make_shared<RotationTransform>(.05f, glm::vec3{ 1, 0, 0 }));
		break;

	case GLFW_KEY_L:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(std::make_shared<RotationTransform>(.05f, glm::vec3{ 0, 0, 1 }));
		break;

	case GLFW_KEY_APOSTROPHE:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(std::make_shared<RotationTransform>(-.05f, glm::vec3{ 0, 0, 1 }));
		break;

	case GLFW_KEY_U:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 0.9f, 0.9f, 0.9f }));
		break;

	case GLFW_KEY_I:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 1.1f, 1.1f, 1.1f }));
		break;
	}
}
