#pragma once
#include <string>
#include <fstream>

class ShaderImporter
{
private:
	static const std::string DEFAULT_PATH;
public:
	static std::string readFile(std::string fileName);
};
