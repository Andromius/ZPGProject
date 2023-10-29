#include "Shader.h"
#include <vector>

void Shader::compile()
{
	glCompileShader(shader);
	
    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<GLchar> infoLog(infoLogLength);
        glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog.data());

        printf("\n%s", infoLog.data());
    }
}

void Shader::setSource(const char* shaderSource)
{
	glShaderSource(shader, 1, &shaderSource, nullptr);
}

GLuint Shader::get()
{
	return shader;
}

Shader::~Shader() {}
