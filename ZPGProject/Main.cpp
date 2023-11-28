#include "Application.h"
#include <windows.h>
#include <iostream>

int main(void)
{
	wchar_t buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);

	// The variable 'buffer' now contains the full path of the executable
	std::wcout << "Path: " << buffer << std::endl;

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
