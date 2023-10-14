#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "Scene.h"
#include "Window.h"
#include "Camera.h"

#include "Shaders/Shader.h"  
#include "Shaders/FragmentShader.h"
#include "Shaders/VertexShader.h"
#include "Shaders/ShaderProgram.h"

#include "Events/EventHandlers.h"
#include "Events/EventNotifier.h"

#include "Transforms/CompositeTransform.h"

class Application : public ErrorEventHandler
{
private:
	static Application* _instance;

	Window* _window;
	Scene* _scene;
	Camera* _camera;
	std::vector<ShaderProgram*> _shaderPrograms;

	void Unsubscribe();

public:
	static Application* getInstance();
	~Application();
	void initialize();
	void createShaders();
	void createModels();
	void run();

	// Inherited via ErrorEventHandler
	void onError(int error, const char* description) override;
};

