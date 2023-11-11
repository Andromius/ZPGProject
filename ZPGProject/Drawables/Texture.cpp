#include "Texture.h"
#include <SOIL.h>

Texture::Texture(std::string filePath)
{
	//Bind the first texture to the first texture unit.
	glActiveTexture(GL_TEXTURE0);
	_textureUnitId = GL_TEXTURE0;
	_samplingConstant = 1;
	//2D texture
	_textureId = SOIL_load_OGL_texture(filePath.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

GLuint Texture::getTextureId()
{
	return _textureId;
}

int Texture::getTextureUnitId()
{
	return _textureUnitId;
}

void Texture::setSamplingConstant(int newSamplingConstant)
{
	_samplingConstant = newSamplingConstant;
}

int Texture::getSamplingConstant()
{
	return _samplingConstant;
}
