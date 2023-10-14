#include "Scene.h"

Scene::Scene(std::vector<DrawableObject*> meshes)
{
	this->objects = std::move(meshes);
	EventNotifier::GetInstance()->subscribeKey(this);
}

Scene::Scene()
{
	this->objects = std::vector<DrawableObject*>();
	EventNotifier::GetInstance()->subscribeKey(this);
}

Scene::~Scene()
{
	objects.erase(objects.begin(), objects.end());
}

void Scene::addDrawableObject(DrawableObject* object)
{
	objects.push_back(object);
}

void Scene::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (DrawableObject* object : objects)
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
			objects[selectedObjectIndex]->addTransform(new TranslateTransform({ 0, .01f, 0 }));
		break;

	case GLFW_KEY_DOWN:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(new TranslateTransform({ 0, -.01f, 0 }));
		break;

	case GLFW_KEY_LEFT:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(new TranslateTransform({ -.01f, 0, 0 }));
		break;

	case GLFW_KEY_RIGHT:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(new TranslateTransform({ .01f, 0, 0 }));
		break;

	case GLFW_KEY_O:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(new RotationTransform(-.05f, { 0, 1, 0 }));
		break;

	case GLFW_KEY_LEFT_BRACKET:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(new RotationTransform(.05f, { 0, 1, 0 }));
		break;

	case GLFW_KEY_P:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(new RotationTransform(-.05f, { 1, 0, 0 }));
		break;

	case GLFW_KEY_SEMICOLON:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(new RotationTransform(.05f, { 1, 0, 0 }));
		break;

	case GLFW_KEY_L:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(new RotationTransform(.05f, { 0, 0, 1 }));
		break;

	case GLFW_KEY_APOSTROPHE:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(new RotationTransform(-.05f, { 0, 0, 1 }));
		break;

	case GLFW_KEY_U:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(new ScaleTransform({ 0.9f, 0.9f, 0.9f }));
		break;

	case GLFW_KEY_I:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			objects[selectedObjectIndex]->addTransform(new ScaleTransform({ 1.1f, 1.1f, 1.1f }));
		break;
	}
}
