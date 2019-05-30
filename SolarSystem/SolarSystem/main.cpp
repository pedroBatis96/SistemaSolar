#include "scene.h"
#include "scenerunner.h"
#define GLEW_STATIC

int main(int argc, char* argv[])
{
	SceneRunner runner("Sistema Solar");
	std::unique_ptr<Scene> scene;
	scene = std::unique_ptr<Scene>(new SceneTexture());

	return runner.run(*scene);
}
