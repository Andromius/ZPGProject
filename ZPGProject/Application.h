#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <map>

#include "Shaders/ShaderProgram.h"

#include "Scene.h"
#include "Events/WindowEventHandler.h"
#include "Camera.h"

#include "Transforms/CompositeTransform.h"
#include <Events/ApplicationEventHandler.h>

class Application : 
	public WindowEventHandler,
	public ObservableObject<ApplicationEventHandler>
{
private:
	size_t _currentScene;
	std::shared_ptr<Window> _window;
	std::vector<std::shared_ptr<Scene>> _scenes;
	std::map<std::string, std::shared_ptr<Mesh>> _meshes;
	std::shared_ptr<Camera> _camera;
	std::map<std::string, std::shared_ptr<ShaderProgram>> _shaderPrograms;

	static void onError(int error, const char* description);
	std::shared_ptr<Scene> createSceneA();
	std::shared_ptr<Scene> createSceneB();
	std::shared_ptr<Scene> createSceneC();

public:
	static Application& getInstance();
	~Application();
	void initialize();
	void createShaders();
	void createModels();
	void createScenes();
	void run();
	Scene& getCurrentScene();

	void onKey(GLFWwindow* window) override;

	// Inherited via ObservableObject
	void notify(int message) override;
};

