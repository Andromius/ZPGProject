#include "Scene.h"
#include "Transforms/RotationTransform.h"
#include "Transforms/ScaleTransform.h"
#include "Application.h"
#include <Lights/PointLight.h>
#include <Transforms/ContinuousBezierTransform.h>

int Scene::getLightIndex(void* ptr)
{
    return std::distance(_lights.begin(),
        std::find_if(_lights.begin(), _lights.end(), [&](std::shared_ptr<Light> l) { return l.get() == ptr; }));
}

int Scene::getObjectIndex(DrawableObject* object)
{
    int objId = std::distance(_objects.begin(),
        std::find_if(_objects.begin(), _objects.end(), [&](std::shared_ptr<DrawableObject> o) { return o.get() == object; }));
    return objId > 255 ? 255 : objId;
}

glm::vec3 Scene::getWorldSpaceCoordsOnCursorPos(ScreenDimensions& dimensions, double xpos, double ypos, float depth)
{
    std::shared_ptr<Camera> cam = Application::getInstance().getCamera();
    glm::vec3 screenX = glm::vec3(xpos, ypos, depth);
    glm::mat4 view = cam->getViewMatrix();
    glm::mat4 projection = cam->getProjectionMatrix();
    glm::vec4 viewPort = glm::vec4(0, 0, dimensions.width, dimensions.height);
    return glm::unProject(screenX, view, projection, viewPort);
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    if(_skybox)
        _skybox->draw();
    glClear(GL_DEPTH_BUFFER_BIT);
	for (auto& object : _objects)
	{
        object->setId(getObjectIndex(object.get()));
        glStencilFunc(GL_ALWAYS, object->getId(), 0xFF);
		object->draw();
	}
}

void Scene::setSkybox(std::shared_ptr<DrawableObject> skybox)
{
    _skybox = skybox;
}

void Scene::setAmbientColorFactor(glm::vec4 ambientColorFactor)
{
    _ambientColorFactor = ambientColorFactor;
}

glm::vec4 Scene::getAmbientColorFactor()
{
    return _ambientColorFactor;
}

void Scene::onKey(GLFWwindow* window)
{
    if (this != &Application::getInstance().getCurrentScene()) return;

    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
    {
        canAddObject = !canAddObject;
        canRemoveObject = false;
        canAssignDirection = false;
        printf("%d canAddObject\n", canAddObject);
    }

    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        canRemoveObject = !canRemoveObject;
        canAddObject = false;
        canAssignDirection = false;
        printf("%d canRemoveObject\n", canRemoveObject);
    }

    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
    {
        canAssignDirection = !canAssignDirection;
        canRemoveObject = false;
        canAddObject = false;
        printf("%d canAssignDirection\n", canAssignDirection);
    }

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

void Scene::onMouseButton(GLFWwindow* window)
{
    if (this != &Application::getInstance().getCurrentScene()) return;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        ScreenDimensions dimensions = _window->getDimensions();
        ypos = dimensions.height - (int)ypos;

        GLbyte color[4];
        GLfloat depth;
        GLuint index;
        glReadPixels((int)xpos, (int)ypos, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
        glReadPixels((int)xpos, (int)ypos, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
        glReadPixels((int)xpos, (int)ypos, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
        
        printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth% f, stencil index % u\n", 
            (int)xpos, (int)ypos, color[0], color[1], color[2], color[3], depth, index);
        
        glm::vec3 pos = getWorldSpaceCoordsOnCursorPos(dimensions, xpos, ypos, depth);
        if (!canAssignDirection)
        {
            selectedObjectIndex = index;
            _pointsCache.clear();
        }

        if (canAssignDirection)
        {
            int i = 0;
            CompositeTransform* ct = _objects[selectedObjectIndex]->getComposite();
            while (true)
            {
                Transform* tr = ct->getTransform(i);
                if (!tr)
                {
                    _pointsCache.push_back(pos);
                    ct->addContinuousBezierTransform(0.01, 0);
                    break;
                }
                
                ContinuousBezierTransform* cbt = dynamic_cast<ContinuousBezierTransform*>(tr);
                if (!cbt)
                {
                    i++;
                    continue;
                }
                
                _pointsCache.push_back(pos);
                if (_pointsCache.size() == 2 && cbt->hasFirstCurve())
                {
                    glm::mat4 mat = ct->transformUntil(i);
                    glm::vec3 tlVec = glm::vec3(mat[3] / mat[3].w);
                    cbt->addPoint(_pointsCache[0] - tlVec, _pointsCache[1] - tlVec);
                    _pointsCache.clear();
                }
                else if (_pointsCache.size() == 4 && !cbt->hasFirstCurve())
                {
                    glm::mat4 mat = ct->transformUntil(i);
                    glm::vec3 tlVec = glm::vec3(mat[3] / mat[3].w);
                    cbt->addPoints(glm::mat4x3(_pointsCache[0] - tlVec, _pointsCache[1] - tlVec, _pointsCache[2] - tlVec, _pointsCache[3] - tlVec));
                    _pointsCache.clear();
                }
                break;
            }
        }

        if (canAddObject)
        {
            this->addDrawableObject(Application::getInstance().getPresetObject(pos));
        }

        if (canRemoveObject)
        {
            if (Application::getInstance().isGift(_objects[index]))
            {
                _objects.erase(_objects.begin() + index);
                selectedObjectIndex--;
                printf("IT WAS A GIFT!\n");
            }
        }

        printf("WorldPos %f %f %f\n", pos.x, pos.y, pos.z);
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
