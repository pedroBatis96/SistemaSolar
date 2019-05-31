#include "cookbookogl.h"
#include "scene.h"
#include "scenetexture.h"
#include <GLFW/glfw3.h>
#include "glutils.h"

#define WIN_WIDTH 1200
#define WIN_HEIGHT 800

#include <map>
#include <string>

class SceneRunner {
private:
	GLFWwindow* window;
	int fbw, fbh;

public:
	SceneRunner(const std::string& windowTitle, int width = WIN_WIDTH, int height = WIN_HEIGHT, int samples = 0) {
		// Initialize GLFW
		if (!glfwInit()) exit(EXIT_FAILURE);

#ifdef __APPLE__
		// Select OpenGL 4.1
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#else
		// Select OpenGL 4.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#endif
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		if (samples > 0) {
			glfwWindowHint(GLFW_SAMPLES, samples);
		}

		// Open the window
		window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, windowTitle.c_str(), NULL, NULL);
		if (!window) {
			glfwTerminate();
			exit(EXIT_FAILURE);
		}
		glfwMakeContextCurrent(window);

		// Get framebuffer size
		glfwGetFramebufferSize(window, &fbw, &fbh);

		// Load the OpenGL functions.
		if (!gladLoadGL()) { exit(-1); }

		GLUtils::dumpGLInfo();

		// Initialization
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
#ifndef __APPLE__
		glDebugMessageCallback(GLUtils::debugCallback, NULL);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
		glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 0,
			GL_DEBUG_SEVERITY_NOTIFICATION, -1, "Start debugging");
#endif
	}

	int run(Scene& scene) {
		scene.setDimensions(fbw, fbh);
		scene.initScene();
		scene.resize(fbw, fbh);

		glfwSetKeyCallback(window, SceneTexture::keyfunc);

		// Enter the main loop
		mainLoop(window, scene);

		// Close window and terminate GLFW
		glfwTerminate();

		// Exit program
		return EXIT_SUCCESS;
	}

	static std::string parseCLArgs(int argc, char** argv, std::map<std::string, std::string>& sceneData) {
		if (argc < 2) {
			printHelpInfo(argv[0], sceneData);
			exit(EXIT_FAILURE);
		}

		std::string recipeName = argv[1];
		auto it = sceneData.find(recipeName);
		if (it == sceneData.end()) {
			printf("Unknown recipe: %s\n\n", recipeName.c_str());
			printHelpInfo(argv[0], sceneData);
			exit(EXIT_FAILURE);
		}

		return recipeName;
	}

private:
	static void printHelpInfo(const char* exeFile, std::map<std::string, std::string>& sceneData) {
		printf("Usage: %s recipe-name\n\n", exeFile);
		printf("Recipe names: \n");
		for (auto it : sceneData) {
			printf("  %11s : %s\n", it.first.c_str(), it.second.c_str());
		}
	}

	void mainLoop(GLFWwindow* window, Scene& scene) {
		while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			GLUtils::checkForOpenGLError(__FILE__, __LINE__);
			scene.update(float(glfwGetTime()));
			scene.render();
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
};

void  SceneTexture::keyfunc(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		SceneTexture::paused = !SceneTexture::paused;

	}

	if (key == GLFW_KEY_W && action == GLFW_REPEAT) {
		if (camx > 500) {
			camx -= 100.0f;
			printf("X:%.2f Y:%.2f Z%.2f\n", camx, camy, camz);
		}

	}
	if (key == GLFW_KEY_S && action == GLFW_REPEAT) {
		if (camx < 3300) {
			camx += 100.0f;
			printf("X:%.2f Y:%.2f Z%.2f\n", camx, camy, camz);
		}
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		if (camx > 500) {
			camx -= 50.0f;
			printf("X:%.2f Y:%.2f Z%.2f\n", camx, camy, camz);
		}
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		if (camx < 3300) {
			camx += 50.0f;
			printf("X:%.2f Y:%.2f Z%.2f\n", camx, camy, camz);
		}
	}


	if (key == GLFW_KEY_A && action == GLFW_REPEAT) {
		if (camy < 1800) {
			camy += 100.0f;
			printf("X:%.2f Y:%.2f Z%.2f\n", camx, camy, camz);
		}
	}
	if (key == GLFW_KEY_D && action == GLFW_REPEAT) {
		if (camy > -1800) {
			camy -= 100.0f;
			printf("X:%.2f Y:%.2f Z%.2f\n", camx, camy, camz);
		}
	}

	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		if (camy < 1800) {
			camy += 50.0f;
			printf("X:%.2f Y:%.2f Z%.2f\n", camx, camy, camz);
		}
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		if (camy > -1800) {
			camy -= 50.0f;
			printf("X:%.2f Y:%.2f Z%.2f\n", camx, camy, camz);
		}
	}


	if (key == GLFW_KEY_Q && action == GLFW_REPEAT) {
		if (camz < 1800) {
			camz += 100.0f;
			printf("X:%.2f Y:%.2f Z%.2f\n", camx, camy, camz);
		}
	}
	if (key == GLFW_KEY_E && action == GLFW_REPEAT) {
		if (camz > -1800) {
			camz -= 100.0f;
			printf("X:%.2f Y:%.2f Z%.2f\n", camx, camy, camz);
		}
	}

	if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		if (camz < 1800) {
			camz += 50.0f;
			printf("X:%.2f Y:%.2f Z%.2f\n", camx, camy, camz);
		}
	}
	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		if (camz > -1800) {
			camz -= 50.0f;
			printf("X:%.2f Y:%.2f Z%.2f\n", camx, camy, camz);
		}
	}


	if (key == GLFW_KEY_V && action == GLFW_PRESS) {
		SceneTexture::is2d = !SceneTexture::is2d;
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		SceneTexture::paused = true;
		SceneTexture::isMenu = true;
		SceneTexture::camx = 800.00;
		SceneTexture::camy = 200.00;
		SceneTexture::camz = 50.00;
		SceneTexture::selected = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 3; j++) {
				SceneTexture::planetlocations[i][j] = SceneTexture::planetDefaultlocations[i][j];
			}
		}
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		if (SceneTexture::isMenu) {
			if ((SceneTexture::selected < 7))
				SceneTexture::selected += 1;
			else
				SceneTexture::selected = -1;
			if (selected != -1) {
				printf("Selected:Planet %d\n", SceneTexture::selected);
				SceneTexture::eyex = SceneTexture::planetlocations[selected][0];
				SceneTexture::eyey = SceneTexture::planetlocations[selected][1];
				SceneTexture::eyez = SceneTexture::planetlocations[selected][2];
				SceneTexture::camz = SceneTexture::planetlocations[selected][2] + 50.0f;
			}
			else {
				printf("Selected:Sun\n");
				SceneTexture::eyex = SceneTexture::starLocation[0][0];
				SceneTexture::eyey = SceneTexture::starLocation[0][1];
				SceneTexture::eyez = SceneTexture::starLocation[0][2];
				SceneTexture::camz = SceneTexture::starLocation[0][2] + 50.0f;
			}
		}
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		if (SceneTexture::isMenu) {
			if ((SceneTexture::selected > -1))
				SceneTexture::selected -= 1;
			else
				SceneTexture::selected = 7;
			if (selected != -1) {
				printf("Selected:Planet %d\n", SceneTexture::selected);
				SceneTexture::eyex = SceneTexture::planetlocations[selected][0];
				SceneTexture::eyey = SceneTexture::planetlocations[selected][1];
				SceneTexture::eyez = SceneTexture::planetlocations[selected][2];
				SceneTexture::camz = SceneTexture::planetlocations[selected][2] + 50.0f;
			}
			else {
				printf("Selected:Sun\n");
				SceneTexture::eyex = SceneTexture::starLocation[0][0];
				SceneTexture::eyey = SceneTexture::starLocation[0][1];
				SceneTexture::eyez = SceneTexture::starLocation[0][2];
				SceneTexture::camz = SceneTexture::starLocation[0][2] + 50.0f;
			}
		}
	}

	if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		SceneTexture::paused = false;
		SceneTexture::isMenu = false;
		SceneTexture::eyex = 0.f;
		SceneTexture::eyey = 0.f;
		SceneTexture::eyez = 0.f;
	}
}
