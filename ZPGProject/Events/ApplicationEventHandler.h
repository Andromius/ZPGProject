#pragma once
#include "Scene.h"

class ApplicationEventHandler
{
public:
	virtual void onSceneChanged(Scene& scene);
};