#include "ShaderProgram.h"
#include "Events/Messages/Message.h"
#include "Application.h"

ShaderProgram::ShaderProgram(std::shared_ptr<Camera> camera, VertexShader& vertexShader, FragmentShader& fragmentShader)
{
	_program = glCreateProgram();
	glAttachShader(_program, vertexShader.get());
	glAttachShader(_program, fragmentShader.get());
	_camera = camera;
	_camera->subscribe(this);
	Application::getInstance().subscribe(this);
	link();
	onEvent(CAM_POSITION_CHANGED | CAM_PROJ_MAT_CHANGED | CAM_VIEW_MAT_CHANGED);
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

void ShaderProgram::setMatrixVariable(glm::mat4 matrix, std::string name)
{
	const GLint id = glGetUniformLocation(_program, name.c_str());
	glProgramUniformMatrix4fv(_program, id, 1, GL_FALSE, value_ptr(matrix));
}

void ShaderProgram::setVec3Variable(glm::vec3 vector, std::string name)
{
	const GLint id = glGetUniformLocation(_program, name.c_str());
	glProgramUniform3fv(_program, id, 1, value_ptr(vector));
}

void ShaderProgram::setVec4Variable(glm::vec4 vector, std::string name)
{
	const GLint id = glGetUniformLocation(_program, name.c_str());
	glProgramUniform4fv(_program, id, 1, value_ptr(vector));
}

void ShaderProgram::resetProgram()
{
	glUseProgram(0);
}

void ShaderProgram::onEvent(int message)
{
	if (message & CAM_POSITION_CHANGED)
		setVec3Variable(_camera->getEye(), "cameraPosition");

	if (message & CAM_VIEW_MAT_CHANGED)
		setMatrixVariable(_camera->getCamera(), "viewMatrix");

	if (message & CAM_PROJ_MAT_CHANGED)
		setMatrixVariable(_camera->getPerspective(), "projectionMatrix");

	if (message & APP_SCENE_CHANGED)
	{
		for (auto& light : Application::getInstance().getCurrentScene().getLights())
		{
			setVec3Variable(light->_position, "lightPosition");
			setVec4Variable(light->_color, "lightColor");
		}
	}
}
