#include "Scene.h"
#include "Events/Messages/Message.h"
#include "Transforms/RotationTransform.h"
#include "Transforms/ScaleTransform.h"
#include "Application.h"

Scene::Scene(std::shared_ptr<Window> window)
{
	_objects = std::vector<std::shared_ptr<DrawableObject>>();
    _lights = std::vector<std::shared_ptr<Light>>();
    _window = window;
    _window->subscribe(this);
}

Scene::~Scene()
{
    _window->unsubscribe(this);
}

void Scene::addDrawableObject(std::shared_ptr<DrawableObject> object)
{
	_objects.push_back(object);
}

void Scene::addLight(std::shared_ptr<Light> light)
{
    _lights.push_back(light);
}

std::vector<std::shared_ptr<Light>> Scene::getLights()
{
    return _lights;
}

void Scene::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (auto& object : _objects)
	{
		object->draw();
	}
}

void Scene::onKey(GLFWwindow* window)
{
    Scene& s = Application::getInstance().getCurrentScene();
    if (glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS) {
        if (s.selectedObjectIndex < s._objects.size() - 1)
            s.selectedObjectIndex++;
        else
            s.selectedObjectIndex = 0;
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        s._objects[selectedObjectIndex]->addTransform(std::make_shared<TranslateTransform>(glm::vec3{ 0, 0.01f, 0 }));

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        s._objects[selectedObjectIndex]->addTransform(std::make_shared<TranslateTransform>(glm::vec3{ 0, -0.01f, 0 }));

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        s._objects[selectedObjectIndex]->addTransform(std::make_shared<TranslateTransform>(glm::vec3{ -0.01f, 0, 0 }));

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        s._objects[selectedObjectIndex]->addTransform(std::make_shared<TranslateTransform>(glm::vec3{ 0.01f, 0, 0 }));

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        s._objects[selectedObjectIndex]->addTransform(std::make_shared<RotationTransform>(-0.05f, glm::vec3{ 0, 1, 0 }));

    if (glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS)
        s._objects[selectedObjectIndex]->addTransform(std::make_shared<RotationTransform>(0.05f, glm::vec3{ 0, 1, 0 }));

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        s._objects[selectedObjectIndex]->addTransform(std::make_shared<RotationTransform>(-0.05f, glm::vec3{ 1, 0, 0 }));

    if (glfwGetKey(window, GLFW_KEY_SEMICOLON) == GLFW_PRESS)
        s._objects[selectedObjectIndex]->addTransform(std::make_shared<RotationTransform>(0.05f, glm::vec3{ 1, 0, 0 }));

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        s._objects[selectedObjectIndex]->addTransform(std::make_shared<RotationTransform>(0.05f, glm::vec3{ 0, 0, 1 }));

    if (glfwGetKey(window, GLFW_KEY_APOSTROPHE) == GLFW_PRESS)
        s._objects[selectedObjectIndex]->addTransform(std::make_shared<RotationTransform>(-0.05f, glm::vec3{ 0, 0, 1 }));

    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
        s._objects[selectedObjectIndex]->addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 0.9f, 0.9f, 0.9f }));

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        s._objects[selectedObjectIndex]->addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 1.1f, 1.1f, 1.1f }));
}