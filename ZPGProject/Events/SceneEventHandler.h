#pragma once
#include <vector>
#include "Light.h"
class SceneEventHandler
{
public:
    virtual void onSceneLightsChanged(std::vector<std::shared_ptr<Light>>& lights);
};