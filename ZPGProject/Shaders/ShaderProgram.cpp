#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(Camera* camera)
{
	_program = glCreateProgram();
	_camera = camera;
	_camera->subscribe(this);
	_projectionMatrix = _camera->getPerspective();
	_viewMatrix = _camera->getCamera();
}

ShaderProgram::~ShaderProgram()
{
	_camera->unsubscribe(this);
}

void ShaderProgram::attachShaders(std::vector<Shader*> shaders)
{
	for (Shader* shader : shaders)
	{
		glAttachShader(_program, shader->get());
	}
}

void ShaderProgram::link()
{
	glLinkProgram(_program);
}

void ShaderProgram::useProgram()
{
	glUseProgram(_program);
	setMatrixVariable(_projectionMatrix, "projectionMatrix");
	setMatrixVariable(_viewMatrix, "viewMatrix");
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
	glUniformMatrix4fv(id, 1, GL_FALSE, value_ptr(matrix));
}

void ShaderProgram::resetProgram()
{
	glUseProgram(0);
}

void ShaderProgram::onCameraChanged()
{
	_projectionMatrix = _camera->getPerspective();
	_viewMatrix = _camera->getCamera();
}
