#include "SkyboxTexture.h"
#include <SOIL.h>

SkyboxTexture::SkyboxTexture(std::string filePathX, std::string filePathXNeg, std::string filePathY, std::string filePathYNeg, std::string filePathZ, std::string filePathZNeg)
{
	glActiveTexture(GL_TEXTURE0);
	_textureUnitId = GL_TEXTURE0;
	_samplingConstant = 1;
	//2D texture
	_textureId = SOIL_load_OGL_cubemap(filePathX.c_str(), filePathXNeg.c_str(), filePathY.c_str(), filePathYNeg.c_str(), filePathZ.c_str(), filePathZNeg.c_str(),
		SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
