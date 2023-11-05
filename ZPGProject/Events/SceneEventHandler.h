#pragma once
#include <vector>
#include <Lights/Light.h>
class SceneEventHandler
{
public:
    virtual void onSceneLightPositionChanged(int index, glm::vec3 position);
    virtual void onSceneLightColorChanged(int index, glm::vec4 color);
    virtual void onSceneLightDirectionChanged(int index, glm::vec3 direction);
};