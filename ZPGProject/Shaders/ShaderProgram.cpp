#include "ShaderProgram.h"
#include "Application.h"
#include <format>
#include <iostream>
#include <Lights/PointLight.h>
#include <Lights/DirectionalLight.h>
#include <Lights/LightType.h>
#include <Lights/SpotLight.h>

ShaderProgram::ShaderProgram(std::shared_ptr<Camera> camera, VertexShader& vertexShader, FragmentShader& fragmentShader)
{
	_program = glCreateProgram();
	glAttachShader(_program, vertexShader.get());
	glAttachShader(_program, fragmentShader.get());
	_camera = camera;
	_scene = nullptr;
	_camera->subscribe(this);
	Application::getInstance().subscribe(this);
	link();

	onCameraPositionChanged(_camera->getEye());
	onCameraProjectionMatrixChanged(_camera->getProjectionMatrix());
	onCameraViewMatrixChanged(_camera->getViewMatrix());
}

ShaderProgram::~ShaderProgram()
{
	Application::getInstance().unsubscribe(this);
	_camera->unsubscribe(this);
}

void ShaderProgram::link()
{
	glLinkProgram(_program);
}

void ShaderProgram::useProgram()
{
	glUseProgram(_program);
}

void ShaderProgram::checkStatus()
{
	GLint status;
	glGetProgramiv(_program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(_program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}

void ShaderProgram::setVariable(glm::mat4 matrix, std::string name)
{
	const GLint id = glGetUniformLocation(_program, name.c_str());
	glProgramUniformMatrix4fv(_program, id, 1, GL_FALSE, value_ptr(matrix));
}

void ShaderProgram::setVariable(glm::vec3 vector, std::string name)
{
	const GLint id = glGetUniformLocation(_program, name.c_str());
	glProgramUniform3fv(_program, id, 1, value_ptr(vector));
}

void ShaderProgram::setVariable(glm::vec4 vector, std::string name)
{
	const GLint id = glGetUniformLocation(_program, name.c_str());
	glProgramUniform4fv(_program, id, 1, value_ptr(vector));
}

void ShaderProgram::setVariable(float value, std::string name)
{
	const GLint id = glGetUniformLocation(_program, name.c_str());
	glProgramUniform1f(_program, id, value);
}

void ShaderProgram::setVariable(int value, std::string name)
{
	const GLint id = glGetUniformLocation(_program, name.c_str());
	glProgramUniform1i(_program, id, value);
}

void ShaderProgram::setMaterial(Material& material)
{
	setVariable(material.getColor(), "objectColor");
	setVariable(material.getSpecularStrength(), "specularStrength");
	setVariable(material.getShininess(), "shininess");
}

void ShaderProgram::setTexture(Texture& texture)
{
	setVariable(texture.getTextureUnitId(), "textureUnitID");
	setVariable(texture.getSamplingConstant(), "samplingConstant");
}

void ShaderProgram::resetProgram()
{
	glUseProgram(0);
}

void ShaderProgram::onCameraPositionChanged(glm::vec3 position)
{
	setVariable(position, "cameraPosition");
}

void ShaderProgram::onCameraProjectionMatrixChanged(glm::mat4 matrix)
{
	setVariable(matrix, "projectionMatrix");
}

void ShaderProgram::onCameraViewMatrixChanged(glm::mat4 matrix)
{
	setVariable(matrix, "viewMatrix");
}

void ShaderProgram::setLightVariables(std::shared_ptr<Light> light, int i)
{
	setVariable(light->getColor(), "lights[" + std::to_string(i) + "].color");
	setVariable(light->getDiffuseStrength(), "lights[" + std::to_string(i) + "].diffuseStrength");

	std::shared_ptr<PointLight> pLight = std::dynamic_pointer_cast<PointLight>(light);
	if (pLight)
	{
		setVariable(pLight->getPosition(), "lights[" + std::to_string(i) + "].position");
		setVariable(pLight->getAttenuation(), "lights[" + std::to_string(i) + "].attenuation");
		std::shared_ptr<SpotLight> sLight = std::dynamic_pointer_cast<SpotLight>(pLight);
		if (sLight)
		{
			setVariable(sLight->getAngle(), "lights[" + std::to_string(i) + "].angle");
			setVariable(sLight->getAngleFadeStart(), "lights[" + std::to_string(i) + "].angleFadeStart");
			setVariable(sLight->getDirection(), "lights[" + std::to_string(i) + "].direction");
			setVariable(LightType::SPOT, "lights[" + std::to_string(i) + "].type");
		}
		else
			setVariable(LightType::POINT, "lights[" + std::to_string(i) + "].type");
	}

	std::shared_ptr<DirectionalLight> dLight = std::dynamic_pointer_cast<DirectionalLight>(light);
	if (dLight)
	{
		setVariable(dLight->getDirection(), "lights[" + std::to_string(i) + "].direction");
		setVariable(LightType::DIRECTIONAL, "lights[" + std::to_string(i) + "].type");
	}
}

void ShaderProgram::onSceneChanged(Scene& scene)
{
	if (_scene != nullptr)
		_scene->unsubscribe(this);
	_scene = &scene;

	scene.subscribe(this);
	std::vector<std::shared_ptr<Light>> lights = scene.getLights();
	setVariable((int)lights.size(), "numberOfLights");

	for (size_t i = 0; i < lights.size(); i++)
	{
		setLightVariables(lights[i], i);
	}
}

void ShaderProgram::onSceneLightPositionChanged(int index, glm::vec3 position)
{
	setVariable(position, "lights[" + std::to_string(index) + "].position");
}

void ShaderProgram::onSceneLightColorChanged(int index, glm::vec4 color)
{
	setVariable(color, "lights[" + std::to_string(index) + "].color");
}

void ShaderProgram::onSceneLightDirectionChanged(int index, glm::vec3 direction)
{
	setVariable(direction, "lights[" + std::to_string(index) + "].direction");
}
