#pragma once
#include "glm/glm.hpp"

class LightEventHandler
{
public:
    virtual void onLightPositionChanged(glm::vec3 position, void* ptr);
    virtual void onLightColorChanged(glm::vec4 color, void* ptr);
    virtual void onLightDirectionChanged(glm::vec3 direction, void* ptr);
};