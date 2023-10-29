#include "ShaderImporter.h"

const std::string ShaderImporter::DEFAULT_PATH = "Shaders/Definitions/";

std::string ShaderImporter::readFile(std::string fileName)
{
    std::ifstream fileStream(DEFAULT_PATH + fileName);

    if (!fileStream.is_open()) return "";

    std::string out((std::istreambuf_iterator<char>(fileStream)), (std::istreambuf_iterator<char>()));
    fileStream.close();

    if (out[0] != '\xEF' && out[1] != '\xBB' && out[2] != '\xBF') {
        return out;
    }
    else {
        out.erase(0, 3);
        return out;
    }
}
