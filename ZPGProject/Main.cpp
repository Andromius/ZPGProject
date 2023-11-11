#include "Application.h"

int main(void)
{
	Application& app = Application::getInstance();
	app.initialize();
	app.createShaders();
	app.createModels();
	app.createMaterials();
	app.loadTextures();
	app.createScenes();
	app.run();

	exit(EXIT_SUCCESS);
}
