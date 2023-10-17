#include "Application.h"
#include "Meshes/suzi_flat.h"
#include "Meshes/suzi_smooth.h"
#include "Meshes/sphere.h"
#include "Meshes/square.h"
#include "Shaders/ShaderImporter.h"
#include <iostream>

const char* fragment_shader =
"#version 330\n"
"out vec4 frag_colour;"
"in vec3 pos;"
"void main () {"
"     frag_colour = vec4(pos, 1.0);"
"}";

const char* fragment_shader2 =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (0.0, 1.0, 1.0, 1.0);"
"}";

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
	_shaderPrograms = std::vector<std::shared_ptr<ShaderProgram>>();

	EventNotifier::getInstance().subscribeError(this);

	glfwSetErrorCallback(EventNotifier::notifyError);

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	_window = std::make_shared<Window>(800, 600, "ZPG", nullptr, nullptr);

	if (!_window->get()) {
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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);

	int width, height;
	glfwGetFramebufferSize(_window->get(), &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
	glfwSetInputMode(_window->get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	_scene = std::make_shared<Scene>();
	_camera = std::make_shared<Camera>(glm::vec3(0, 0, 3), glm::vec3(0, 0, -4), glm::vec3(0, 1, 0), 60.0f, 800.0f, 600.0f, 0.1f);
}

void Application::createShaders()
{
	std::string vertexShader = ShaderImporter::readFile("vertexShader.vert");
	std::cout << vertexShader << std::endl;
	std::string fragmentShader = ShaderImporter::readFile("fragmentShader.frag");
	std::cout << fragmentShader << std::endl;

	//create and compile shaders
	std::vector<std::shared_ptr<Shader>> shaders
	{
		std::make_shared<VertexShader>(vertexShader.c_str()),
		std::make_shared<FragmentShader>(fragmentShader.c_str())
	};
	_shaderPrograms.push_back(std::make_shared<ShaderProgram>(_camera));
	_shaderPrograms[0]->attachShaders(shaders);
	_shaderPrograms[0]->link();

	std::vector<std::shared_ptr<Shader>> shaders2
	{
		std::make_shared<VertexShader>(vertexShader.c_str()),
		std::make_shared<FragmentShader>(fragment_shader2)
	};
	_shaderPrograms.push_back(std::make_shared<ShaderProgram>(_camera));
	_shaderPrograms[1]->attachShaders(shaders2);
	_shaderPrograms[1]->link();

	for (auto& shaderProgram : _shaderPrograms)
	{
		shaderProgram->checkStatus();
	}
}

void Application::createModels()
{
	std::shared_ptr<DrawableObject> o1 = std::make_shared<DrawableObject>(std::make_shared<Mesh>(square), _shaderPrograms[1]);
	o1->addTransform(std::make_shared<RotationTransform>(glm::radians(90.f), glm::vec3(1,0,0)))
		.addTransform(std::make_shared<TranslateTransform>(glm::vec3( 0, 0, 1.0f )))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 2, 2, 2 }));
	_scene->addDrawableObject(o1);

	std::shared_ptr<DrawableObject> suzi = std::make_shared<DrawableObject>(std::make_shared<Mesh>(suziFlat), _shaderPrograms[0]);
	suzi->addTransform(std::make_shared<TranslateTransform>(glm::vec3{ 0.5f, .4f, .3f }))
		.addTransform(std::make_shared<RotationTransform>(glm::radians(45.f), glm::vec3{ 0, 1, 0 }))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ .2f, .2f, .2f }));
	_scene->addDrawableObject(suzi);

	std::shared_ptr<DrawableObject> suzi2 = std::make_shared<DrawableObject>(std::make_shared<Mesh>(suziSmooth), _shaderPrograms[0]);
	suzi2->addTransform(std::make_shared<TranslateTransform>(glm::vec3{ 0.5f, .4f, 5.f }))
		.addTransform(std::make_shared<RotationTransform>(glm::radians(45.f), glm::vec3{ 0, 1, 0 }))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ .2f, .2f, .2f }));
	_scene->addDrawableObject(suzi2);

	std::shared_ptr<DrawableObject> o2 = std::make_shared<DrawableObject>(std::make_shared<Mesh>(square), _shaderPrograms[1]);
	o2->addTransform(std::make_shared<RotationTransform>(glm::radians(90.f), glm::vec3{ 1,0,0 }))
		.addTransform(std::make_shared<TranslateTransform>(glm::vec3{ 0, 0, -2.0f }))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 2, 2, 2 }));
	_scene->addDrawableObject(o2);

	std::shared_ptr<DrawableObject> sphereObj = std::make_shared<DrawableObject>(std::make_shared<Mesh>(sphere), _shaderPrograms[0]);
	sphereObj->addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 0.2f, 0.2f, 0.2f }));
	_scene->addDrawableObject(sphereObj);

}

void Application::run()
{
	while (!glfwWindowShouldClose(_window->get())) {
		// clear color and depth buffer

		_scene->draw();
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(_window->get());
	}
}

void Application::onError(int error, const char* description)
{
	fputs(description, stderr);
}