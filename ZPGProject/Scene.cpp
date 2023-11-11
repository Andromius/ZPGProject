#include "Scene.h"
#include "Transforms/RotationTransform.h"
#include "Transforms/ScaleTransform.h"
#include "Application.h"
#include <Lights/PointLight.h>

int Scene::getLightIndex(void* ptr)
{
    return std::distance(_lights.begin(),
        std::find_if(_lights.begin(), _lights.end(), [&](std::shared_ptr<Light> l) { return l.get() == ptr; }));
}

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
    light->subscribe(this);
    _lights.push_back(light);
}

std::vector<std::shared_ptr<Light>> Scene::getLights()
{
    return _lights;
}

void Scene::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(_skybox)
        _skybox->draw();
    glClear(GL_DEPTH_BUFFER_BIT);
	for (auto& object : _objects)
	{
		object->draw();
	}
}

void Scene::setSkybox(std::shared_ptr<DrawableObject> skybox)
{
    _skybox = skybox;
}

void Scene::onKey(GLFWwindow* window)
{
    if (this != &Application::getInstance().getCurrentScene()) return;

    if (glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS) {
        if (selectedObjectIndex < _objects.size() - 1)
            selectedObjectIndex++;
        else
            selectedObjectIndex = 0;
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        _objects[selectedObjectIndex]->addTransform(std::make_shared<TranslateTransform>(glm::vec3{ 0, 0.01f, 0 }));

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        _objects[selectedObjectIndex]->addTransform(std::make_shared<TranslateTransform>(glm::vec3{ 0, -0.01f, 0 }));

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        _objects[selectedObjectIndex]->addTransform(std::make_shared<TranslateTransform>(glm::vec3{ -0.01f, 0, 0 }));

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        _objects[selectedObjectIndex]->addTransform(std::make_shared<TranslateTransform>(glm::vec3{ 0.01f, 0, 0 }));

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        _objects[selectedObjectIndex]->addTransform(std::make_shared<RotationTransform>(-0.05f, glm::vec3{ 0, 1, 0 }));

    if (glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS)
        _objects[selectedObjectIndex]->addTransform(std::make_shared<RotationTransform>(0.05f, glm::vec3{ 0, 1, 0 }));

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        _objects[selectedObjectIndex]->addTransform(std::make_shared<RotationTransform>(-0.05f, glm::vec3{ 1, 0, 0 }));

    if (glfwGetKey(window, GLFW_KEY_SEMICOLON) == GLFW_PRESS)
        _objects[selectedObjectIndex]->addTransform(std::make_shared<RotationTransform>(0.05f, glm::vec3{ 1, 0, 0 }));

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        _objects[selectedObjectIndex]->addTransform(std::make_shared<RotationTransform>(0.05f, glm::vec3{ 0, 0, 1 }));

    if (glfwGetKey(window, GLFW_KEY_APOSTROPHE) == GLFW_PRESS)
        _objects[selectedObjectIndex]->addTransform(std::make_shared<RotationTransform>(-0.05f, glm::vec3{ 0, 0, 1 }));

    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
        _objects[selectedObjectIndex]->addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 0.9f, 0.9f, 0.9f }));

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        _objects[selectedObjectIndex]->addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 1.1f, 1.1f, 1.1f }));

    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)
    {
        std::shared_ptr<PointLight> light = std::dynamic_pointer_cast<PointLight>(_lights[0]);
        if (light)
        {
            glm::vec3 pos = light->getPosition();
            pos.y += 0.5;
            light->setPosition(pos);
        }
    }

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)
    {
        std::shared_ptr<PointLight> light = std::dynamic_pointer_cast<PointLight>(_lights[0]);
        if (light)
        {
            glm::vec3 pos = light->getPosition();
            pos.y -= 0.5;
            light->setPosition(pos);
        }
    }

    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
    {
        std::shared_ptr<PointLight> light = std::dynamic_pointer_cast<PointLight>(_lights[0]);
        if (light)
        {
            glm::vec3 pos = light->getPosition();
            pos.x += 0.5;
            light->setPosition(pos);
        }
    }

    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
    {
        std::shared_ptr<PointLight> light = std::dynamic_pointer_cast<PointLight>(_lights[0]);
        if (light)
        {
            glm::vec3 pos = light->getPosition();
            pos.x -= 0.5;
            light->setPosition(pos);
        }
    }

    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS)
    {
        std::shared_ptr<PointLight> light = std::dynamic_pointer_cast<PointLight>(_lights[0]);
        if (light)
        {
            glm::vec3 pos = light->getPosition();
            pos.z += 0.5;
            light->setPosition(pos);
        }
    }

    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS)
    {
        std::shared_ptr<PointLight> light = std::dynamic_pointer_cast<PointLight>(_lights[0]);
        if (light)
        {
            glm::vec3 pos = light->getPosition();
            pos.z -= 0.5;
            light->setPosition(pos);
        }
    }
}

void Scene::onLightColorChanged(glm::vec4 color, void* ptr)
{
    notify(&SceneEventHandler::onSceneLightColorChanged, getLightIndex(ptr), color);
}

void Scene::onLightPositionChanged(glm::vec3 position, void* ptr)
{
    notify(&SceneEventHandler::onSceneLightPositionChanged, getLightIndex(ptr), position);
}

void Scene::onLightDirectionChanged(glm::vec3 direction, void* ptr)
{
    notify(&SceneEventHandler::onSceneLightDirectionChanged, getLightIndex(ptr), direction);
}
