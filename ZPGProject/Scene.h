#pragma once
#include <vector>
#include "Meshes/Mesh.h"
#include "Drawables/DrawableObject.h"
#include "Events/EventHandlers.h"
#include "Events/EventNotifier.h"
#include "Transforms/RotationTransform.h"
#include "Transforms/ScaleTransform.h"

class Scene : 
	public KeyEventHandler
{
private:
	int selectedObjectIndex = 0;
	std::vector<std::shared_ptr<DrawableObject>> objects;

public:
	Scene(std::vector<std::shared_ptr<DrawableObject>> objects);
	Scene();
	~Scene();

	void addDrawableObject(std::shared_ptr<DrawableObject> objects);
	void draw();

	// Inherited via KeyEventHandler
	void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) override;
};

