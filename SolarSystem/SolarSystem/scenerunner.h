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

void planetInformation(int selected) {
	switch (selected) {
	case -1:
		printf("Sol\n");
		printf("Radius : 695,508km\n");
		printf("Mass : 1,989,100,000,000,000,000,000,000,000,000kg\n");
		break;
	case 0:
		printf("Mercurio\n");
		printf("Radius : 2,439.7km\n");
		printf("Mass : 330,104,000,000,000,000,000,000kg\n");
		break;
	case 1:
		printf("Venus\n");
		printf("Radius : 6,051.8km\n");
		printf("Mass : 4,867,320,000,000,000,000,000,000kg\n");
		break;
	case 2:
		printf("Terra\n");
		printf("Radius : 6,371.00km\n");
		printf("Mass : 5,972,190,000,000,000,000,000,000kg\n");
		break;
	case 3:
		printf("Marte\n");
		printf("Radius : 3,389.5km\n");
		printf("Mass : 641,693,000,000,000,000,000,000kg\n");
		break;
	case 4:
		printf("Jupiter\n");
		printf("Radius : 69,911km\n");
		printf("Mass : 898,130,000,000,000,000,000,000,000kg\n");
		break;
	case 5:
		printf("Saturno\n");
		printf("Radius : 58,232km\n");
		printf("Mass : 568,319,000,000,000,000,000,000,000kg\n");
		break;
	case 6:
		printf("Urano\n");
		printf("Radius : 25,362km\n");
		printf("Mass : 86,810,300,000,000,000,000,000,000kg\n");
		break;
	case 7:
		printf("Neptuno\n");
		printf("Radius : 24,622km\n");
		printf("Mass : 102,410,000,000,000,000,000,000,000kg\n");
		break;
	}
}


void  SceneTexture::keyfunc(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		if (!isMenu) {
			paused = !paused;
		}

	}

	if (key == GLFW_KEY_CAPS_LOCK && action == GLFW_PRESS) {
		isTroll = !isTroll;
	}

	if (key == GLFW_KEY_W && action == GLFW_REPEAT) {
		if (camx > 500) {
			camx -= 100.0f;
		}

	}
	if (key == GLFW_KEY_S && action == GLFW_REPEAT) {
		if (camx < 3300) {
			camx += 100.0f;
		}
	}

	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		if (camx > 500) {
			camx -= 50.0f;
		}
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		if (camx < 3300) {
			camx += 50.0f;
		}
	}

	if (key == GLFW_KEY_A && action == GLFW_REPEAT) {
		if (camy < 1800) {
			camy += 100.0f;
		}
	}
	if (key == GLFW_KEY_D && action == GLFW_REPEAT) {
		if (camy > -1800) {
			camy -= 100.0f;
		}
	}

	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		if (camy < 1800) {
			camy += 50.0f;
		}
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		if (camy > -1800) {
			camy -= 50.0f;
		}
	}

	if (key == GLFW_KEY_Q && action == GLFW_REPEAT) {
		if (camz < 1800) {
			camz += 100.0f;
		}
	}
	if (key == GLFW_KEY_E && action == GLFW_REPEAT) {
		if (camz > -1800) {
			camz -= 100.0f;
		}
	}

	if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		if (camz < 1800) {
			camz += 50.0f;
		}
	}
	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		if (camz > -1800) {
			camz -= 50.0f;
		}
	}

	if (key == GLFW_KEY_V && action == GLFW_PRESS) {
		if(!is2d)
			printf("Entrou no modo 2d\n");
		else
			printf("Saiu do modo 2d\n");
		is2d = !is2d;
	}

	if (key == GLFW_KEY_M && action == GLFW_PRESS) {
		paused = true;
		isMenu = true;
		camx = 800.00;
		camy = 200.00;
		camz = 50.00;
		selected = -1;
		printf("Carregue na seta da direita ou esquerda para mudar de planeta\n\nCarregue no N para sair do modo menu\n");
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 3; j++) {
				planetlocations[i][j] = planetDefaultlocations[i][j];
			}
		}
	}
	if (key == GLFW_KEY_N && action == GLFW_PRESS) {
		printf("Saiu do modo de menu\n");
		paused = false;
		isMenu = false;
		eyex = 0.f;
		eyey = 0.f;
		eyez = 0.f;
		camx = 2500.0f;
		camy = 500.0f;
		camz = 0.0f;
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		if (isMenu) {
			if ((selected < 7))
				selected += 1;
			else
				selected = -1;
			if (selected != -1) {
				eyex = planetlocations[selected][0];
				eyey = planetlocations[selected][1];
				eyez = planetlocations[selected][2];
				camz = planetlocations[selected][2] + 50.0f;
			}
			else {
				eyex = starLocation[0][0];
				eyey = starLocation[0][1];
				eyez = starLocation[0][2];
				camz = starLocation[0][2] + 50.0f;
			}
			planetInformation(selected);
		}
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		if (isMenu) {
			if ((selected > -1))
				selected -= 1;
			else
				selected = 7;
			if (selected != -1) {
				eyex = planetlocations[selected][0];
				eyey = planetlocations[selected][1];
				eyez = planetlocations[selected][2];
				camz = planetlocations[selected][2] + 50.0f;
			}
			else {
				eyex = starLocation[0][0];
				eyey = starLocation[0][1];
				eyez = starLocation[0][2];
				camz = starLocation[0][2] + 50.0f;
			}
			planetInformation(selected);
		}
	}
	if (key == GLFW_KEY_H && action == GLFW_PRESS) {
		if (isMenu) {
			printf("Carregue na seta da direita ou esquerda para mudar de planeta\n\nCarregue no N para sair do modo menu\n");
			return;
		}
		if (is2d) {
			printf("Carregue no V para sair do modo 2D\n");
			return;
		}
		printf("Carregue no W e S para se mover no eixo dos x\nCarregue no A e D para se mover no eixo dos y\nCarregue no Q e E para se mover no eixo dos z\n");
		printf("Carregue no V para entrar no modo 2D\nCarregue no M para entrar no modo menu\n");
	}
}