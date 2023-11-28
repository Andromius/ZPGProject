#pragma once
#include <vector>
#include <string>
class MeshImporter
{
public:
	static std::vector<float> readFromFile(std::string path);
};