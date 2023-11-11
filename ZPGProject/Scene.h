#pragma once
#include <vector>
#include "Meshes/Mesh.h"
#include "Drawables/DrawableObject.h"
#include "Window.h"
#include <Events/SceneEventHandler.h>
#include <Lights/Light.h>

class Scene : 
	public WindowEventHandler,
	public LightEventHandler,
	public ObservableObject<SceneEventHandler>
{
private:
	size_t selectedObjectIndex = 0;
	std::shared_ptr<Window> _window;
	std::vector<std::shared_ptr<DrawableObject>> _objects;
	std::shared_ptr<DrawableObject> _skybox;
	std::vector<std::shared_ptr<Light>> _lights;

	int getLightIndex(void* ptr);

public:
	Scene(std::shared_ptr<Window> window);
	~Scene();

	void addDrawableObject(std::shared_ptr<DrawableObject> object);
	void addLight(std::shared_ptr<Light> light);
	std::vector<std::shared_ptr<Light>> getLights();
	void draw();
	void setSkybox(std::shared_ptr<DrawableObject> skybox);
	
	void onKey(GLFWwindow* window) override;

	void onLightColorChanged(glm::vec4 color, void* ptr) override;
	void onLightPositionChanged(glm::vec3 position, void* ptr) override;
	void onLightDirectionChanged(glm::vec3 direction, void* ptr) override;
};

