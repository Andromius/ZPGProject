#include "Application.h"
#include "Meshes/suzi_flat.h"
#include "Meshes/suzi_smooth.h"
#include "Meshes/sphere.h"
#include "Meshes/square.h"

Application* Application::_instance = new Application();

const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 vn;"
"uniform mat4 modelMatrix;"
"uniform mat4 viewMatrix;"
"uniform mat4 projectionMatrix;"
"out vec3 pos;"
"void main () {"
"     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);"
"	  pos = vn;"
"}";

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

void Application::Unsubscribe()
{
	EventNotifier::GetInstance()->unsubscribeError(this);
}

Application* Application::getInstance()
{
	return _instance;
}

Application::~Application()
{
	Unsubscribe();
	_shaderPrograms.erase(_shaderPrograms.begin(), _shaderPrograms.end());
	delete _scene;
	delete _window;
	glfwTerminate();
}

void Application::initialize()
{
	_shaderPrograms = std::vector<ShaderProgram*>();

	EventNotifier::GetInstance()->subscribeError(this);
	glfwSetErrorCallback(EventNotifier::notifyError);

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	_window = new Window(800, 600, "ZPG", NULL, NULL);

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
	_scene = new Scene();
	_camera = new Camera({ 0, 0, 3 }, { 0, 0, -4 }, { 0, 1, 0 }, 45.0f, 800.0f, 600.0f, 0.1f);
}

void Application::createShaders()
{
	//create and compile shaders
	std::vector<Shader*> shaders
	{
		new VertexShader(vertex_shader),
		new FragmentShader(fragment_shader)
	};
	_shaderPrograms.push_back(new ShaderProgram(_camera));
	_shaderPrograms[0]->attachShaders(shaders);
	_shaderPrograms[0]->link();

	shaders.erase(shaders.begin(), shaders.end());

	std::vector<Shader*> shaders2
	{
		new VertexShader(vertex_shader),
		new FragmentShader(fragment_shader2)
	};
	_shaderPrograms.push_back(new ShaderProgram(_camera));
	_shaderPrograms[1]->attachShaders(shaders2);
	_shaderPrograms[1]->link();

	shaders2.erase(shaders2.begin(), shaders2.end());

	for (auto shaderProgram : _shaderPrograms)
	{
		shaderProgram->checkStatus();
	}
}

void Application::createModels()
{
	DrawableObject* o1 = new DrawableObject(new Mesh(square), _shaderPrograms[1]);
	o1->addTransform(new RotationTransform(glm::radians(90.f), {1,0,0}))
		->addTransform(new TranslateTransform({ 0, 0, 1.0f }))
		->addTransform(new ScaleTransform({ 2, 2, 2 }));
	_scene->addDrawableObject(o1);

	DrawableObject* suzi = new DrawableObject(new Mesh(suziFlat), _shaderPrograms[0]);
	suzi->addTransform(new TranslateTransform({ 0.5f, .4f, .3f }))
		->addTransform(new RotationTransform(glm::radians(45.f), { 0, 1, 0 }))
		->addTransform(new ScaleTransform({ .2f, .2f, .2f }));
	_scene->addDrawableObject(suzi);

	DrawableObject* suzi2 = new DrawableObject(new Mesh(suziSmooth), _shaderPrograms[0]);
	suzi2->addTransform(new TranslateTransform({ 0.5f, .4f, 5.f }))
		->addTransform(new RotationTransform(glm::radians(45.f), { 0, 1, 0 }))
		->addTransform(new ScaleTransform({ .2f, .2f, .2f }));
	_scene->addDrawableObject(suzi2);

	DrawableObject* o2 = new DrawableObject(new Mesh(square), _shaderPrograms[1]);
	o2->addTransform(new RotationTransform(glm::radians(90.f), { 1,0,0 }))
		->addTransform(new TranslateTransform({ 0, 0, -2.0f }))
		->addTransform(new ScaleTransform({ 2, 2, 2 }));
	_scene->addDrawableObject(o2);

	DrawableObject* sphereObj = new DrawableObject(new Mesh(sphere), _shaderPrograms[0]);
	sphereObj->addTransform(new ScaleTransform({ 0.2f, 0.2f, 0.2f }));
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