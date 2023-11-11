#pragma once
#include <string>
#include <GL/glew.h>
class Texture
{
protected:
	GLuint _textureId;
	int _textureUnitId;
	int _samplingConstant;
	Texture();


public:
	Texture(std::string filePath);
	GLuint getTextureId();
	int getTextureUnitId();

	void setSamplingConstant(int newSamplingConstant);
	int getSamplingConstant();
};