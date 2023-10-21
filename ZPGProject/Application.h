#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include <map>

#include "Shaders/Shader.h"  
#include "Shaders/FragmentShader.h"
#include "Shaders/VertexShader.h"
#include "Shaders/ShaderProgram.h"

#include "Scene.h"
#include "Window.h"
#include "Camera.h"

#include "Transforms/CompositeTransform.h"

class Application : 
	public EventHandler,
	public KeyEventHandler,
	public ObservableObject
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

	// Inherited via EventHandler
	void onEvent(int message) override;

	// Inherited via KeyEventHandler
	void onKey(GLFWwindow* window) override;
};

