#pragma once
#include <string>
#include <GL/glew.h>
class Texture
{
private:
	GLuint _textureId;
	int _textureUnitId;
	int _samplingConstant;


public:
	Texture(std::string filePath);
	GLuint getTextureId();
	int getTextureUnitId();

	void setSamplingConstant(int newSamplingConstant);
	int getSamplingConstant();
};