#pragma once
#include "Texture.h"

class SkyboxTexture : public Texture
{
public:
	SkyboxTexture(std::string filePathX, std::string filePathXNeg, std::string filePathY, std::string filePathYNeg, std::string filePathZ, std::string filePathZNeg);
	void bind() override;
};