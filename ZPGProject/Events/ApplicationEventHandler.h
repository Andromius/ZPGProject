#pragma once

class Scene;
class ApplicationEventHandler
{
public:
	virtual void onSceneChanged(Scene& scene);
};