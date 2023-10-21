#include "Application.h"
#include "Meshes/suzi_flat.h"
#include "Meshes/suzi_smooth.h"
#include "Meshes/sphere.h"
#include "Meshes/square.h"
#include "Shaders/ShaderImporter.h"
#include "Events/Messages/Message.h"
#include "Shaders/Shader.h"  
#include "Shaders/FragmentShader.h"
#include "Shaders/VertexShader.h"

Application& Application::getInstance()
{
	static Application instance = Application();
	return instance;
}

Application::~Application()
{
	_shaderPrograms.erase(_shaderPrograms.begin(), _shaderPrograms.end());
	glfwTerminate();
}

void Application::initialize()
{
	_shaderPrograms = std::map<std::string, std::shared_ptr<ShaderProgram>>();
	_scenes = std::vector<std::shared_ptr<Scene>>();
	_meshes = std::map<std::string, std::shared_ptr<Mesh>>();
	_currentScene = 2;

	glfwSetErrorCallback(onError);

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	_window = std::make_shared<Window>(800, 600, "ZPG", nullptr, nullptr);
	_window->subscribe(this);

	if (!_window->getGLFWWindow()) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	_window->setAsCurrentContext();
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	glEnable(GL_DEPTH_TEST);

	_camera = std::make_shared<Camera>(glm::vec3(0, 0, 3), glm::vec3(0, 0, -4), glm::vec3(0, 1, 0), 60.0f, 0.05f, _window);
}

void Application::createShaders()
{
	VertexShader vertexShader("vertexShader");
	FragmentShader phong("fragmentShaderPhong");
	FragmentShader solid("fragmentShaderSolid");
	FragmentShader lambert("fragmentShaderLambert");
	FragmentShader blinn("fragmentShaderBlinn");

	_shaderPrograms.insert(std::make_pair("phongProgram", std::make_shared<ShaderProgram>(_camera, vertexShader, phong)));
	_shaderPrograms.insert(std::make_pair("lambertProgram", std::make_shared<ShaderProgram>(_camera, vertexShader, lambert)));
	_shaderPrograms.insert(std::make_pair("solidProgram", std::make_shared<ShaderProgram>(_camera, vertexShader, solid)));
	_shaderPrograms.insert(std::make_pair("blinnProgram", std::make_shared<ShaderProgram>(_camera, vertexShader, blinn)));

	for (auto& shaderProgram : _shaderPrograms)
	{
		shaderProgram.second->checkStatus();
	}
}

void Application::createModels()
{
	_meshes.insert(std::make_pair("suziFlat", std::make_shared<Mesh>(suziFlat)));
	_meshes.insert(std::make_pair("suziSmooth", std::make_shared<Mesh>(suziSmooth)));
	_meshes.insert(std::make_pair("square", std::make_shared<Mesh>(square)));
	_meshes.insert(std::make_pair("sphere", std::make_shared<Mesh>(sphere)));
}

void Application::createScenes()
{
	_scenes.push_back(createSceneA());
	_scenes.push_back(createSceneB());
	_scenes.push_back(createSceneC());
	notify(APP_SCENE_CHANGED);
}

void Application::run()
{
	while (!glfwWindowShouldClose(_window->getGLFWWindow())) {
		// clear color and depth buffer

		_scenes[_currentScene]->draw();
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(_window->getGLFWWindow());
	}
}

Scene& Application::getCurrentScene()
{
	return *_scenes[_currentScene];
}

void Application::onKey(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		if (_currentScene < _scenes.size() - 1) _currentScene++;
		else _currentScene = 0;
		notify(APP_SCENE_CHANGED);
	}
}

void Application::notify(int message)
{
	for (auto& subscriber : _subscribers)
	{
		if (message & APP_SCENE_CHANGED)
			subscriber->onSceneChanged(*_scenes[_currentScene]);
	}
}

void Application::onError(int error, const char* description)
{
	fputs(description, stderr);
}

std::shared_ptr<Scene> Application::createSceneA()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>(_window);

	std::shared_ptr<DrawableObject> sphereA = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongProgram"]);
	sphereA->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0.0f, 0.0f, 1.0f)))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 0.2f, 0.2f, 0.2f }));
	scene->addDrawableObject(sphereA);

	scene->addLight(std::make_shared<Light>(glm::vec3(0, 0, 0)));

	return scene;
}

std::shared_ptr<Scene> Application::createSceneB()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>(_window);

	std::shared_ptr<DrawableObject> sphereA = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongProgram"]);
	sphereA->addTransform(std::make_shared<TranslateTransform>(glm::vec3(-0.5f, 0.0f, 0.0f)))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 0.2f, 0.2f, 0.2f }));
	scene->addDrawableObject(sphereA);

	std::shared_ptr<DrawableObject> sphereB = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongProgram"]);
	sphereB->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0.5f, 0.0f, 0.0f)))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 0.2f, 0.2f, 0.2f }));
	scene->addDrawableObject(sphereB);

	std::shared_ptr<DrawableObject> sphereC = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongProgram"]);
	sphereC->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0.0f, 0.5f, 0.0f)))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 0.2f, 0.2f, 0.2f }));
	scene->addDrawableObject(sphereC);

	std::shared_ptr<DrawableObject> sphereD = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongProgram"]);
	sphereD->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0.0f, -0.5f, 0.0f)))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 0.2f, 0.2f, 0.2f }));
	scene->addDrawableObject(sphereD);

	scene->addLight(std::make_shared<Light>(glm::vec3(0, 0, 0)));

	return scene;
}

std::shared_ptr<Scene> Application::createSceneC()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>(_window);

	std::shared_ptr<DrawableObject> o1 = std::make_shared<DrawableObject>(_meshes["square"], _shaderPrograms["solidProgram"]);
	o1->addTransform(std::make_shared<RotationTransform>(glm::radians(90.f), glm::vec3(1, 0, 0)))
		.addTransform(std::make_shared<TranslateTransform>(glm::vec3(0, 0, 1.0f)))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 2, 2, 2 }));
	scene->addDrawableObject(o1);

	std::shared_ptr<DrawableObject> o2 = std::make_shared<DrawableObject>(_meshes["square"], _shaderPrograms["solidProgram"]);
	o2->addTransform(std::make_shared<RotationTransform>(glm::radians(90.f), glm::vec3{ 1,0,0 }))
		.addTransform(std::make_shared<TranslateTransform>(glm::vec3(0, 0, -2.0f)))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 2, 2, 2 }));
	scene->addDrawableObject(o2);

	std::shared_ptr<DrawableObject> suzi = std::make_shared<DrawableObject>(_meshes["suziFlat"], _shaderPrograms["lambertProgram"]);
	suzi->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0.5f, 0, 0)))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ .2f, .2f, .2f }));
	scene->addDrawableObject(suzi);

	std::shared_ptr<DrawableObject> suzi2 = std::make_shared<DrawableObject>(_meshes["suziSmooth"], _shaderPrograms["blinnProgram"]);
	suzi2->addTransform(std::make_shared<TranslateTransform>(glm::vec3{ 0, 0.5, 0}))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ .2f, .2f, .2f }));
	scene->addDrawableObject(suzi2);

	std::shared_ptr<DrawableObject> sphereObj = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongProgram"]);
	sphereObj->addTransform(std::make_shared<TranslateTransform>(glm::vec3(-0.5f, 0.0f, 0.0f)))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 0.2f, 0.2f, 0.2f }));
	scene->addDrawableObject(sphereObj);

	scene->addLight(std::make_shared<Light>(glm::vec3(0, 0, 0)));

	return scene;
}
