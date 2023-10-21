#pragma once
#include <vector>
#include "Meshes/Mesh.h"
#include "Drawables/DrawableObject.h"
#include "Window.h"
#include "Light.h"

class Scene : 
	public WindowEventHandler
{
private:
	size_t selectedObjectIndex = 0;
	std::shared_ptr<Window> _window;
	std::vector<std::shared_ptr<DrawableObject>> _objects;
	std::vector<std::shared_ptr<Light>> _lights;

public:
	Scene(std::shared_ptr<Window> window);
	~Scene();

	void addDrawableObject(std::shared_ptr<DrawableObject> object);
	void addLight(std::shared_ptr<Light> light);
	std::vector<std::shared_ptr<Light>> getLights();
	void draw();
	
	void onKey(GLFWwindow* window) override;
};

