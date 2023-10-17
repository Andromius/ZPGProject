#include "ShaderImporter.h"

const std::string ShaderImporter::DEFAULT_PATH = "Shaders/Definitions/";

std::string ShaderImporter::readFile(std::string fileName)
{
    std::ifstream fileStream(DEFAULT_PATH + fileName);

    if (!fileStream.is_open()) return "";

    std::string out((std::istreambuf_iterator<char>(fileStream)), (std::istreambuf_iterator<char>()));

    fileStream.close();

    return out;
}
