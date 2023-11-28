#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <map>

#include "Shaders/ShaderProgram.h"
#include "Drawables/Texture.h"

#include "Scene.h"
#include "Events/WindowEventHandler.h"
#include "Camera.h"

#include "Transforms/CompositeTransform.h"
#include "Events/ApplicationEventHandler.h"

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
	std::shared_ptr<SpotLight> _cameraLight;
	std::map<std::string, std::shared_ptr<ShaderProgram>> _shaderPrograms;
	std::map<std::string, std::shared_ptr<Material>> _materials;
	std::map<std::string, std::shared_ptr<Texture>> _textures;


	static void onError(int error, const char* description);
	std::shared_ptr<Scene> createSceneA();
	std::shared_ptr<Scene> createSceneB();
	std::shared_ptr<Scene> createSceneC();
	std::shared_ptr<Scene> createSceneD();
	std::shared_ptr<Scene> createSceneE();
	std::shared_ptr<Scene> createSceneF();
	std::shared_ptr<Scene> createSceneG();

public:
	static Application& getInstance();
	~Application();
	void initialize();
	void createShaders();
	void createModels();
	void createScenes();
	void createMaterials();
	void loadTextures();
	void run();
	Scene& getCurrentScene();
	std::shared_ptr<Camera> getCamera();
	std::shared_ptr<DrawableObject> getPresetObject(glm::vec3 translation);
	bool isGift(std::shared_ptr<DrawableObject> candidate);

	void onKey(GLFWwindow* window) override;
};

