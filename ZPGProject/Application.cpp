#include "Application.h"
#include "Meshes/suzi_flat.h"
#include "Meshes/suzi_smooth.h"
#include "Meshes/sphere.h"
#include "Meshes/square.h"
#include "Meshes/bushes.h"
#include "Meshes/tree.h"
#include "Meshes/gift.h"
#include "Meshes/triangle.h"
#include "Meshes/skycube.h"
#include "Shaders/ShaderImporter.h"
#include "Shaders/Shader.h"  
#include "Shaders/FragmentShader.h"
#include "Shaders/VertexShader.h"
#include <Transforms/GeneralAxisRotationTransform.h>
#include <Lights/PointLight.h>
#include <Lights/DirectionalLight.h>
#include <Lights/SpotLight.h>
#include <Meshes/TextureMesh.h>
#include <Meshes/SkyboxMesh.h>
#include <Drawables/SkyboxTexture.h>
#include <Meshes/MeshImporter.h>
#include <Util.h>
#include <Transforms/ContinuousLineTransform.h>
#include <Transforms/ContinuousBezierTransform.h>

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
	_textures = std::map<std::string, std::shared_ptr<Texture>>();
	_currentScene = 6;

	glfwSetErrorCallback(onError);

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	_window = std::make_shared<Window>(800, 600, "ZPG", nullptr, nullptr);
	//_camera = std::make_shared<Camera>(glm::vec3(0, 0, 2), glm::vec3(0, 0, -4), glm::vec3(0, 1, 0), 60.0f, 0.05f, _window);
	_camera = std::make_shared<Camera>(glm::vec3(0, 8, -3), glm::vec3(0, -45, 4), glm::vec3(0, 1, 0), 60.0f, 0.05f, _window);
	_cameraLight = std::make_shared<SpotLight>(15.f, 10.f, glm::vec3(0, 0, -2), glm::vec3(0, 0, 1), glm::vec4(1, 1, 1, 1), 0.1, 0, 1);
	_camera->attachLight(_cameraLight);
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
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

}

void Application::createShaders()
{
	VertexShader vertexShader("vertexShader");
	FragmentShader phong("fragmentShaderPhong");
	FragmentShader phongNoRing("fragmentShaderPhongNoRing");
	FragmentShader solid("fragmentShaderSolid");
	FragmentShader lambert("fragmentShaderLambert");
	FragmentShader blinn("fragmentShaderBlinn");
	FragmentShader blinnNoRing("fragmentShaderBlinnNoRing");
	VertexShader texTestVert("textureTest");
	FragmentShader texTestFrag("textureTest");
	VertexShader skyboxVert("vertexShaderSkybox");
	FragmentShader skyboxFrag("fragmentShaderSkybox");
	FragmentShader tomPhong("fragmentShaderTomPhong");
	FragmentShader skydomeFrag("fragmentShaderSkyDome");

	_shaderPrograms.insert(std::make_pair("phongTomProgram", std::make_shared<ShaderProgram>(_camera, vertexShader, tomPhong)));
	_shaderPrograms.insert(std::make_pair("phongProgram", std::make_shared<ShaderProgram>(_camera, vertexShader, phong)));
	_shaderPrograms.insert(std::make_pair("lambertProgram", std::make_shared<ShaderProgram>(_camera, vertexShader, lambert)));
	_shaderPrograms.insert(std::make_pair("solidProgram", std::make_shared<ShaderProgram>(_camera, vertexShader, solid)));
	_shaderPrograms.insert(std::make_pair("blinnProgram", std::make_shared<ShaderProgram>(_camera, vertexShader, blinn)));
	_shaderPrograms.insert(std::make_pair("blinnNoRingProgram", std::make_shared<ShaderProgram>(_camera, vertexShader, blinnNoRing)));
	_shaderPrograms.insert(std::make_pair("phongNoRingProgram", std::make_shared<ShaderProgram>(_camera, vertexShader, phongNoRing)));
	_shaderPrograms.insert(std::make_pair("textureTest", std::make_shared<ShaderProgram>(_camera, vertexShader, texTestFrag)));
	_shaderPrograms.insert(std::make_pair("skybox", std::make_shared<ShaderProgram>(_camera, skyboxVert, skyboxFrag)));
	_shaderPrograms.insert(std::make_pair("skydome", std::make_shared<ShaderProgram>(_camera, skyboxVert, skydomeFrag)));

	
	for (auto& shaderProgram : _shaderPrograms)
	{
		shaderProgram.second->checkStatus();
	}
}

void Application::createModels()
{
	_meshes.insert(std::make_pair("suziFlat", std::make_shared<Mesh>(std::vector<float>(std::begin(suziFlat), std::end(suziFlat)))));
	_meshes.insert(std::make_pair("suziSmooth", std::make_shared<Mesh>(std::vector<float>(std::begin(suziSmooth), std::end(suziSmooth)))));
	_meshes.insert(std::make_pair("square", std::make_shared<Mesh>(square)));
	_meshes.insert(std::make_pair("sphere", std::make_shared<Mesh>(std::vector<float>(std::begin(sphere), std::end(sphere)))));
	_meshes.insert(std::make_pair("bush", std::make_shared<Mesh>(std::vector<float>(std::begin(bushes), std::end(bushes)))));
	_meshes.insert(std::make_pair("tree", std::make_shared<Mesh>(std::vector<float>(std::begin(tree), std::end(tree)))));
	_meshes.insert(std::make_pair("gift", std::make_shared<Mesh>(std::vector<float>(std::begin(gift), std::end(gift)))));
	_meshes.insert(std::make_pair("texTriangle", std::make_shared<TextureMesh>(std::vector<float>(std::begin(triangle), std::end(triangle)))));
	_meshes.insert(std::make_pair("skybox", std::make_shared<SkyboxMesh>(std::vector<float>(std::begin(skycube), std::end(skycube)))));
	_meshes.insert(std::make_pair("importTest", std::make_shared<TextureMesh>(MeshImporter::readFromFile("C:\\Users\\marti\\Downloads\\ukazkaAssimp\\model.obj"))));
	//_meshes.insert(std::make_pair("JaaG", std::make_shared<TextureMesh>(MeshImporter::readFromFile("C:\\Users\\marti\\Desktop\\ZPG\\ZPGProject\\ZPGProject\\Resources\\jaag\\scene.gltf"))));
	//_meshes.insert(std::make_pair("Beaowl", std::make_shared<TextureMesh>(MeshImporter::readFromFile("C:\\Users\\marti\\Desktop\\ZPG\\ZPGProject\\ZPGProject\\Resources\\beaowl\\scene.gltf"))));
	_meshes.insert(std::make_pair("girl", std::make_shared<TextureMesh>(MeshImporter::readFromFile("C:\\Users\\marti\\Desktop\\ZPG\\ZPGProject\\ZPGProject\\Resources\\14-girl-obj\\girl OBJ.obj"))));
	_meshes.insert(std::make_pair("zombie", std::make_shared<TextureMesh>(MeshImporter::readFromFile("..\\ZPGProject\\Resources\\zombie\\zombie.obj"))));
	_meshes.insert(std::make_pair("tails", std::make_shared<TextureMesh>(MeshImporter::readFromFile("..\\ZPGProject\\Resources\\tails-64\\source\\tails 64 model.fbx"))));
	_meshes.insert(std::make_pair("container", std::make_shared<TextureMesh>(MeshImporter::readFromFile("..\\ZPGProject\\Resources\\Container_v1_medium.fbx"))));
	_meshes.insert(std::make_pair("containerLarge", std::make_shared<TextureMesh>(MeshImporter::readFromFile("..\\ZPGProject\\Resources\\Container_v1_large.fbx"))));
	_meshes.insert(std::make_pair("cube", std::make_shared<TextureMesh>(MeshImporter::readFromFile("..\\ZPGProject\\Resources\\cube.obj"))));
	_meshes.insert(std::make_pair("skydome", std::make_shared<TextureMesh>(MeshImporter::readFromFile("..\\ZPGProject\\Resources\\sky\\skydome.obj"))));
}

void Application::createScenes()
{
	_scenes.push_back(createSceneA());
	_scenes.push_back(createSceneB());
	_scenes.push_back(createSceneC());
	_scenes.push_back(createSceneD());
	_scenes.push_back(createSceneE());
	_scenes.push_back(createSceneF());
	_scenes.push_back(createSceneG());
	//for (size_t i = 0; i < _scenes.size(); i++)
	//{
	//	if (i == _scenes.size() - 1)
	//		break;
	//	_scenes[i]->addLight(_cameraLight);
	//}
	for (auto& scene : _scenes)
	{
		scene->addLight(_cameraLight);
	}

	notify<Scene&>(&ApplicationEventHandler::onSceneChanged, getCurrentScene());
}

void Application::createMaterials()
{
	_materials.insert(std::make_pair("default", std::make_shared<Material>()));
	_materials.insert(std::make_pair("redShiny", std::make_shared<Material>(glm::vec4(1, 0, 0, 1))));
	_materials.insert(std::make_pair("greenShiny", std::make_shared<Material>(glm::vec4(0, 1, 0, 1), 1, 1)));
	_materials.insert(std::make_pair("blueShiny", std::make_shared<Material>(glm::vec4(0, 0, 1, 1))));
	_materials.insert(std::make_pair("yellowShiny", std::make_shared<Material>(glm::vec4(1, 1, 0, 1))));
	_materials.insert(std::make_pair("blueShiny32", std::make_shared<Material>(glm::vec4(0, 0, 1, 1), 1, 32)));
	_materials.insert(std::make_pair("black", std::make_shared<Material>(glm::vec4(0.3, 0.7, 0.2, 1), 0.1f, 1)));
	
	_materials.insert(std::make_pair("mercuryGray", std::make_shared<Material>(glm::vec4(0.6627, 0.6627, 0.6627, 1), 1, 32)));
	_materials.insert(std::make_pair("venusOrange", std::make_shared<Material>(glm::vec4(1.0, 0.6471, 0.0, 1), 1, 32)));
	_materials.insert(std::make_pair("earthBlue", std::make_shared<Material>(glm::vec4(0.0, 0.0, 1.0, 1), 1, 1)));
	_materials.insert(std::make_pair("marsReddishOrange", std::make_shared<Material>(glm::vec4(1.0, 0.2706, 0.0, 1), 1, 32)));
	_materials.insert(std::make_pair("jupiterLightOrange", std::make_shared<Material>(glm::vec4(1.0, 0.5451, 0.2706, 1), 1, 32)));
	_materials.insert(std::make_pair("saturnPaleYellow", std::make_shared<Material>(glm::vec4(1.0, 0.8941, 0.7098, 1), 1, 32)));
	_materials.insert(std::make_pair("uranusLightBlue", std::make_shared<Material>(glm::vec4(0.6784, 0.8471, 0.902, 1), 1, 32)));
	_materials.insert(std::make_pair("neptuneDeepBlue", std::make_shared<Material>(glm::vec4(0.1176, 0.5647, 1.0, 1), 1, 32)));
	_materials.insert(std::make_pair("plutoGray", std::make_shared<Material>(glm::vec4(0.502, 0.502, 0.502, 1), 1, 32)));
	_materials.insert(std::make_pair("moonGray", std::make_shared<Material>(glm::vec4(0.7, 0.7, 0.7, 1.0), 1, 32)));
	_materials.insert(std::make_pair("blackHoleDarkGray", std::make_shared<Material>(glm::vec4(0.1, 0.1, 0.1, 1.0), 1, 32)));
}

void Application::loadTextures()
{
	_textures.insert(std::make_pair("default", std::make_shared<Texture>("C:\\Users\\marti\\Desktop\\ZPG\\multipletextures\\grass.png")));
	_textures.insert(std::make_pair("skybox", std::make_shared<SkyboxTexture>(
		"C:\\Users\\marti\\Desktop\\cubemap\\posx.jpg",
		"C:\\Users\\marti\\Desktop\\cubemap\\negx.jpg",
		"C:\\Users\\marti\\Desktop\\cubemap\\posy.jpg",
		"C:\\Users\\marti\\Desktop\\cubemap\\negy.jpg",
		"C:\\Users\\marti\\Desktop\\cubemap\\posz.jpg",
		"C:\\Users\\marti\\Desktop\\cubemap\\negz.jpg")));
	_textures.insert(std::make_pair("nightsky", std::make_shared<SkyboxTexture>(
		"..\\ZPGProject\\Resources\\nightsky\\posx.png",
		"..\\ZPGProject\\Resources\\nightsky\\negx.png",
		"..\\ZPGProject\\Resources\\nightsky\\posy.png",
		"..\\ZPGProject\\Resources\\nightsky\\negy.png",
		"..\\ZPGProject\\Resources\\nightsky\\posz.png",
		"..\\ZPGProject\\Resources\\nightsky\\negz.png")));
	_textures.insert(std::make_pair("houseTexture", std::make_shared<Texture>("C:\\Users\\marti\\Downloads\\ukazkaAssimp\\model.png")));
	_textures.insert(std::make_pair("zombie", std::make_shared<Texture>("..\\ZPGProject\\Resources\\zombie\\zombie.png")));
	_textures.insert(std::make_pair("containerLarge", std::make_shared<Texture>("..\\ZPGProject\\Resources\\T_LargeContainerBackUp_Color.png")));
	_textures.insert(std::make_pair("skydome", std::make_shared<Texture>("..\\ZPGProject\\Resources\\sky\\skydome.png")));
}

void Application::run()
{
	while (!glfwWindowShouldClose(_window->getGLFWWindow())) {
		_scenes[_currentScene]->draw();
		glfwPollEvents();
		glfwSwapBuffers(_window->getGLFWWindow());
	}
}

Scene& Application::getCurrentScene()
{
	return *_scenes[_currentScene];
}

std::shared_ptr<Camera> Application::getCamera()
{
	return _camera;
}

void Application::onKey(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		if (_currentScene < _scenes.size() - 1) _currentScene++;
		else _currentScene = 0;
		notify<Scene&>(&ApplicationEventHandler::onSceneChanged, getCurrentScene());
	}
}

void Application::onError(int error, const char* description)
{
	fputs(description, stderr);
}

std::shared_ptr<DrawableObject> Application::getPresetObject(glm::vec3 translation)
{
	std::shared_ptr<DrawableObject> object = std::make_shared<DrawableObject>(_meshes["gift"], _shaderPrograms["phongProgram"], _materials["blueShiny32"]);
	object->addTransform(std::make_shared<TranslateTransform>(translation));
	return object;
}

bool Application::isGift(std::shared_ptr<DrawableObject> candidate)
{
	return candidate->equals(_meshes["gift"]);
}



#pragma region SceneCreations

std::shared_ptr<Scene> Application::createSceneA()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>(_window);

	std::shared_ptr<DrawableObject> sphereA = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongNoRingProgram"], _materials["default"]);
	sphereA->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0.0f, 0.0f, 1.0f)))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 0.2f, 0.2f, 0.2f }));
	scene->addDrawableObject(sphereA);

	scene->addLight(std::make_shared<PointLight>(glm::vec3(0, 0, 0)));

	return scene;
}

std::shared_ptr<Scene> Application::createSceneB()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>(_window);

	std::shared_ptr<DrawableObject> sphereA = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongProgram"], _materials["blueShiny32"]);
	sphereA->addTransform(std::make_shared<TranslateTransform>(glm::vec3(-0.5f, 0.0f, 0.0f)))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 0.2f, 0.2f, 0.2f }));
	scene->addDrawableObject(sphereA);

	std::shared_ptr<DrawableObject> sphereB = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongProgram"], _materials["blueShiny32"]);
	sphereB->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0.5f, 0.0f, 0.0f)))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 0.2f, 0.2f, 0.2f }));
	scene->addDrawableObject(sphereB);

	std::shared_ptr<DrawableObject> sphereC = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongProgram"], _materials["blueShiny32"]);
	sphereC->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0.0f, 0.5f, 0.0f)))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 0.2f, 0.2f, 0.2f }));
	scene->addDrawableObject(sphereC);

	std::shared_ptr<DrawableObject> sphereD = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongProgram"], _materials["blueShiny32"]);
	sphereD->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0.0f, -0.5f, 0.0f)))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 0.2f, 0.2f, 0.2f }));
	scene->addDrawableObject(sphereD);

	std::shared_ptr<DrawableObject> sphereE = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongProgram"], _materials["blueShiny32"]);
	sphereE->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0.0f, 0.0f, 2.5f)));
	scene->addDrawableObject(sphereE);

	scene->addLight(std::make_shared<PointLight>(glm::vec3(0, 0, 1), glm::vec4(0, 0, 0, 1), 0, 0, 1));

	return scene;
}

std::shared_ptr<Scene> Application::createSceneC()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>(_window);

	std::shared_ptr<DrawableObject> o1 = std::make_shared<DrawableObject>(_meshes["square"], _shaderPrograms["solidProgram"], _materials["default"]);
	o1->addTransform(std::make_shared<RotationTransform>(90.f, glm::vec3(1, 0, 0)))
		.addTransform(std::make_shared<TranslateTransform>(glm::vec3(0, 0, 1.0f)))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 2, 2, 2 }));
	scene->addDrawableObject(o1);

	std::shared_ptr<DrawableObject> o2 = std::make_shared<DrawableObject>(_meshes["square"], _shaderPrograms["solidProgram"], _materials["default"]);
	o2->addTransform(std::make_shared<RotationTransform>(90.f, glm::vec3{ 1,0,0 }))
		.addTransform(std::make_shared<TranslateTransform>(glm::vec3(0, 0, -2.0f)))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 2, 2, 2 }));
	scene->addDrawableObject(o2);

	std::shared_ptr<DrawableObject> suzi = std::make_shared<DrawableObject>(_meshes["suziFlat"], _shaderPrograms["lambertProgram"], _materials["blueShiny32"]);
	suzi->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0.5f, 0, 0)))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ .2f, .2f, .2f }));
	scene->addDrawableObject(suzi);

	std::shared_ptr<DrawableObject> suzi2 = std::make_shared<DrawableObject>(_meshes["suziSmooth"], _shaderPrograms["phongProgram"], _materials["default"]);
	suzi2->addTransform(std::make_shared<TranslateTransform>(glm::vec3{ 0, 0.5, 0}))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ .2f, .2f, .2f }));
	scene->addDrawableObject(suzi2);

	std::shared_ptr<DrawableObject> sphereObj = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongProgram"], _materials["default"]);
	sphereObj->addTransform(std::make_shared<TranslateTransform>(glm::vec3(-0.5f, 0.0f, 0.0f)))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 0.2f, 0.2f, 0.2f }));
	scene->addDrawableObject(sphereObj);

	std::shared_ptr<DrawableObject> sphereObj2 = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongProgram"], _materials["default"]);
	sphereObj2->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0.0f, -0.5f, 0.0f)))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 0.2f, 0.2f, 0.2f }));
	scene->addDrawableObject(sphereObj2);

	scene->addLight(std::make_shared<PointLight>(glm::vec3(0, 0, 0), glm::vec4(1), 0, 0, 1));

	return scene;
}

std::shared_ptr<Scene> Application::createSceneD()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>(_window);

	std::shared_ptr<DrawableObject> sun = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["solidProgram"], _materials["yellowShiny"]);
	sun->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0,0,-3)))
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 0.3f, 0.3f, 0.3f }));
	scene->addDrawableObject(sun);
	
	// Create Mercury
	std::shared_ptr<DrawableObject> mercury = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongProgram"], _materials["mercuryGray"]);
	mercury->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0, 0, -3.4))) // Adjust distance from the Sun
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3(0.03f, 0.03f, 0.03f))); // Adjust scale
	mercury->addTransform(std::make_shared<GeneralAxisRotationTransform>(sun, mercury->getModelMatrix(), glm::vec3(0, 1, 0), 0, 0.3f));
	scene->addDrawableObject(mercury);

	// Create Venus
	std::shared_ptr<DrawableObject> venus = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongProgram"], _materials["venusOrange"]);
	venus->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0, 0, -3.7))) // Adjust distance from the Sun
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3(0.04f, 0.04f, 0.04f))); // Adjust scale
	venus->addTransform(std::make_shared<GeneralAxisRotationTransform>(sun, venus->getModelMatrix(), glm::vec3(0, 1, 0), 0, 0.2f)); // Adjust speed
	scene->addDrawableObject(venus);

	// Create Earth
	std::shared_ptr<DrawableObject> earth = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongNoRingProgram"], _materials["earthBlue"]);
	earth->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0, 0, -4.0))) // Adjust distance from the Sun
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3(0.05f, 0.05f, 0.05f))); // Adjust scale
	earth->addTransform(std::make_shared<GeneralAxisRotationTransform>(sun, earth->getModelMatrix(), glm::vec3(0, 1, 0), 0, 0.2f)); // Adjust speed
	scene->addDrawableObject(earth);

	std::shared_ptr<DrawableObject> moon = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongProgram"], _materials["moonGray"]);
	moon->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0, 0, -4.1))) // Adjust distance from Earth
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3(0.02f, 0.02f, 0.02f))); // Adjust scale
	moon->addTransform(std::make_shared<GeneralAxisRotationTransform>(earth, moon->getModelMatrix(), glm::vec3(0, 1, 0), 0, 2.4f)); // Adjust speed
	scene->addDrawableObject(moon);

	// Create Mars
	std::shared_ptr<DrawableObject> mars = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongProgram"], _materials["marsReddishOrange"]);
	mars->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0, 0, -5.5))) // Adjust distance from the Sun
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3(0.03f, 0.03f, 0.03f))); // Adjust scale
	mars->addTransform(std::make_shared<GeneralAxisRotationTransform>(sun, mars->getModelMatrix(), glm::vec3(0, 1, 0), 0, 0.05f)); // Adjust speed
	scene->addDrawableObject(mars);

	// Create Jupiter
	std::shared_ptr<DrawableObject> jupiter = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongProgram"], _materials["jupiterLightOrange"]);
	jupiter->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0, 0, -8.0))) // Adjust distance from the Sun
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3(0.15f, 0.15f, 0.15f))); // Adjust scale
	jupiter->addTransform(std::make_shared<GeneralAxisRotationTransform>(sun, jupiter->getModelMatrix(), glm::vec3(0, 1, 0), 0, 0.01f)); // Adjust speed
	scene->addDrawableObject(jupiter);

	// Create Saturn
	std::shared_ptr<DrawableObject> saturn = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongProgram"], _materials["saturnPaleYellow"]);
	saturn->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0, 0, -11.0))) // Adjust distance from the Sun
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3(0.1f, 0.1f, 0.1f))); // Adjust scale
	saturn->addTransform(std::make_shared<GeneralAxisRotationTransform>(sun, saturn->getModelMatrix(), glm::vec3(0, 1, 0), 0, 0.006f)); // Adjust speed
	scene->addDrawableObject(saturn);

	// Create Uranus
	std::shared_ptr<DrawableObject> uranus = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongProgram"], _materials["uranusLightBlue"]);
	uranus->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0, 0, -14.0))) // Adjust distance from the Sun
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3(0.07f, 0.07f, 0.07f))); // Adjust scale
	uranus->addTransform(std::make_shared<GeneralAxisRotationTransform>(sun, uranus->getModelMatrix(), glm::vec3(0, 1, 0), 0, 0.002f)); // Adjust speed
	scene->addDrawableObject(uranus);

	// Create Neptune
	std::shared_ptr<DrawableObject> neptune = std::make_shared<DrawableObject>(_meshes["sphere"], _shaderPrograms["phongProgram"], _materials["neptuneDeepBlue"]);
	neptune->addTransform(std::make_shared<TranslateTransform>(glm::vec3(0, 0, -20.0))) // Adjust distance from the Sun
		.addTransform(std::make_shared<ScaleTransform>(glm::vec3(0.08f, 0.08f, 0.08f))); // Adjust scale
	neptune->addTransform(std::make_shared<GeneralAxisRotationTransform>(sun, neptune->getModelMatrix(), glm::vec3(0, 1, 0), 0, 0.001f)); // Adjust speed
	scene->addDrawableObject(neptune);

	scene->addLight(std::make_shared<PointLight>(glm::vec3(0, 0, -3), glm::vec4(1), 0, 0.05f, 0.5f));

	return scene;
}

std::shared_ptr<Scene> Application::createSceneE()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>(_window);

	std::shared_ptr<DrawableObject> ground = std::make_shared<DrawableObject>(_meshes["texTriangle"], _shaderPrograms["textureTest"], _materials["default"]);
	ground->addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 200, 0, 200 }))
		.addTransform(std::make_shared<RotationTransform>(90, glm::vec3(1, 0, 0)));
	_textures["default"]->setSamplingConstant(100);
	ground->setTexture(_textures["default"]);
	scene->addDrawableObject(ground);

	std::shared_ptr<DrawableObject> skybox = std::make_shared<DrawableObject>(_meshes["skybox"], _shaderPrograms["skybox"], _materials["default"]);
	skybox->setTexture(_textures["skybox"]);
	scene->setSkybox(skybox);

	for (size_t i = 0; i < 1000; i++)
	{
		int x = rand() % 50;
		int z = rand() % 50;
		float angle = rand() % 181;
		float scaleFactor = float(rand()) / RAND_MAX;
		std::string meshNames[4] = { "tree", "bush", "gift", "suziSmooth"};
		std::string chosenName = meshNames[rand() % 4];
		std::shared_ptr<DrawableObject> obj = std::make_shared<DrawableObject>(_meshes[chosenName], _shaderPrograms["blinnProgram"], _materials["greenShiny"]);
		obj->addTransform(std::make_shared<TranslateTransform>(glm::vec3{ x, 0, z }))
			.addTransform(std::make_shared<RotationTransform>(angle, glm::vec3(0, 1, 0)))
			.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ scaleFactor, scaleFactor, scaleFactor }));
		scene->addDrawableObject(obj);
	}
	
	scene->addLight(std::make_shared<PointLight>(glm::vec3(0, 5, 0), glm::vec4(1), 0, 0, 0.5));

	return scene;
}

std::shared_ptr<Scene> Application::createSceneF()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>(_window);
	
	std::vector<glm::mat4x3> points {
		glm::mat4x3(
			glm::vec3(-1, 0, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, -1, 0),
			glm::vec3(1, 0, 0)
		)
	};

	glm::mat4 baseFuncCoefs = glm::mat4(
		glm::vec4(-1.0, 3.0, -3.0, 1.0),
		glm::vec4(3.0, -6.0, 3.0, 0),
		glm::vec4(-3.0, 3.0, 0, 0),
		glm::vec4(1, 0, 0, 0));

	std::shared_ptr<DrawableObject> textTr = std::make_shared<DrawableObject>(_meshes["suziSmooth"], _shaderPrograms["phongProgram"], _materials["default"]);
	textTr->addTransform(std::make_shared<TranslateTransform>(glm::vec3(6, 0, 0)))
		.addTransform(std::make_shared<ContinuousBezierTransform>(points, baseFuncCoefs));
	//	.addTransform(std::make_shared<RotationTransform>(90, glm::vec3(1, 0, 0)));
	scene->addDrawableObject(textTr);

	std::shared_ptr<DrawableObject> house = std::make_shared<DrawableObject>(_meshes["importTest"], _shaderPrograms["phongProgram"], _materials["black"]);
	house->setTexture(_textures["houseTexture"]);
	house->addTransform(std::make_shared<TranslateTransform>(glm::vec3(-3, 0, 0)))
		.addTransform(std::make_shared<ContinuousLineTransform>(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)));
	scene->addDrawableObject(house);

	std::shared_ptr<DrawableObject> ground = std::make_shared<DrawableObject>(_meshes["texTriangle"], _shaderPrograms["textureTest"], _materials["black"]);
	ground->addTransform(std::make_shared<TranslateTransform>(glm::vec3(9, 0, 0)));
	ground->setTexture(_textures["houseTexture"]);
	scene->addDrawableObject(ground);

	//scene->addLight(std::make_shared<DirectionalLight>(glm::vec3(1, 1, 0), glm::vec4(1), 0.2));

	return scene;
}

std::shared_ptr<Scene> Application::createSceneG()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>(_window);

	std::shared_ptr<DrawableObject> house = std::make_shared<DrawableObject>(_meshes["importTest"], _shaderPrograms["lambertProgram"], _materials["black"]);
	house->setTexture(_textures["houseTexture"]);
	scene->addDrawableObject(house);

	std::shared_ptr<DrawableObject> ground = std::make_shared<DrawableObject>(_meshes["texTriangle"], _shaderPrograms["phongProgram"], _materials["greenShiny"]);
	ground->addTransform(std::make_shared<ScaleTransform>(glm::vec3{ 50, 1, 50 }));
	_textures["default"]->setSamplingConstant(100);
	ground->setTexture(_textures["default"]);
	scene->addDrawableObject(ground);

	std::vector<glm::mat4x3> points {
		glm::mat4x3(
			glm::vec3(1, 0, 0),
			glm::vec3(2, 0, 1),
			glm::vec3(2, 0, 2),
			glm::vec3(1, 0, 3)
		)
	};

	glm::mat4 baseFuncCoefs = glm::mat4(
		glm::vec4(-1.0, 3.0, -3.0, 1.0),
		glm::vec4(3.0, -6.0, 3.0, 0),
		glm::vec4(-3.0, 3.0, 0, 0),
		glm::vec4(1, 0, 0, 0));
	std::shared_ptr<ContinuousBezierTransform> contBezT = std::make_shared<ContinuousBezierTransform>(points, baseFuncCoefs);
	contBezT->addPoint({ 0, 0, 4 }, { -3, 0, 10 });
	contBezT->addPoint({ -4, 0, 13 }, { -20, 0, 13 });
	contBezT->addPoint({ -25, 0, -13 }, { 0, 0, -20 });
	contBezT->addPoint({ 0, 0, 0 }, { 1, 0, 0 });
	std::shared_ptr<DrawableObject> zombie = std::make_shared<DrawableObject>(_meshes["zombie"], _shaderPrograms["phongProgram"], _materials["black"]);
	zombie->setTexture(_textures["zombie"]);
	zombie->addTransform(std::make_shared<TranslateTransform>(glm::vec3(9, 0, 0)));
		/*.addTransform(contBezT);*/


	scene->addDrawableObject(zombie);

	std::shared_ptr<DrawableObject> container = std::make_shared<DrawableObject>(_meshes["container"], _shaderPrograms["phongProgram"], _materials["greenShiny"]);
	container->addTransform(std::make_shared<TranslateTransform>(glm::vec3(15, 0.33, 0)))
		.addTransform(std::make_shared<RotationTransform>(-90.f, glm::vec3(1,0,0)));
	scene->addDrawableObject(container);

	std::shared_ptr<DrawableObject> containerL = std::make_shared<DrawableObject>(_meshes["containerLarge"], _shaderPrograms["phongProgram"], _materials["greenShiny"]);
	containerL->addTransform(std::make_shared<TranslateTransform>(glm::vec3(25, 0, 0)))
		.addTransform(std::make_shared<RotationTransform>(-90.f, glm::vec3(1, 0, 0)));
	containerL->setTexture(_textures["containerLarge"]);
	scene->addDrawableObject(containerL);

	std::shared_ptr<DrawableObject> skybox = std::make_shared<DrawableObject>(_meshes["skybox"], _shaderPrograms["skybox"], _materials["default"]);
	skybox->setTexture(_textures["nightsky"]);
	scene->setSkybox(skybox);

	std::shared_ptr<DrawableObject> skydome = std::make_shared<DrawableObject>(_meshes["skydome"], _shaderPrograms["skydome"], _materials["default"]);
	skydome->setTexture(_textures["skydome"]);
	//scene->setSkybox(skydome);

	for (size_t i = 0; i < 200; i++)
	{
		int x = Util::getRandomInt(-50, 50);
		int z = Util::getRandomInt(-50, 50);
		float angle = Util::getRandomFloat(-180, 180);
		float scaleFactor = Util::getRandomFloat(0.f, (float)RAND_MAX) / (float)RAND_MAX;
		std::string meshNames[4] = { "tree", "bush", "gift", "zombie" };
		std::string shaderPrograms[4] = { "phongProgram", "phongNoRingProgram", "blinnProgram", "blinnNoRingProgram" };
		std::string chosenName = meshNames[rand() % 4];
		std::string chosenProgram = shaderPrograms[rand() % 4];
		std::shared_ptr<DrawableObject> obj = std::make_shared<DrawableObject>(_meshes[chosenName], _shaderPrograms[chosenProgram], _materials["greenShiny"]);
		obj->addTransform(std::make_shared<TranslateTransform>(glm::vec3{ x, 0, z }))
			.addTransform(std::make_shared<RotationTransform>(angle, glm::vec3(0, 1, 0)))
			.addTransform(std::make_shared<ScaleTransform>(glm::vec3{ scaleFactor, scaleFactor, scaleFactor }));
		if (chosenName == "zombie")
			obj->setTexture(_textures["zombie"]);
		scene->addDrawableObject(obj);
	}

	scene->setAmbientColorFactor(glm::vec4(0.002, 0.002, 0.002, 1));
	scene->addLight(std::make_shared<SpotLight>(30, 25, glm::vec3(15, 1, 0), glm::vec3(1, 0, 0)));
	scene->addLight(std::make_shared<SpotLight>(10, 5, glm::vec3(10, 1, -4), glm::vec3(-1, 0, 0)));
	scene->addLight(std::make_shared<PointLight>(glm::vec3(26, 5, 2), glm::vec4(1,1,1,1), 0, 0.2, 0.2));

	return scene;
}
#pragma endregion


