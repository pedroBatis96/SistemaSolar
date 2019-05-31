#include "scenetexture.h"
#include "texture.h"
#include "stb/stb_image.h"

#include <iostream>
using std::endl;
using std::cerr;

#include <gtc/matrix_transform.hpp>
using glm::vec3;
using glm::mat4;

bool SceneTexture::paused = false, SceneTexture::is2d=false;
GLFWwindow* window;
mat4 translate, scale,rotate;
GLfloat SceneTexture::camx = 2500.0f, SceneTexture::camz = 500.0f;
glm::mat4 modelAux, viewAux, projectionAux;
float x = 0,xplus = 100;

namespace St {
	float starLocation[1][3]{ {0.0f, 0.0f , 0.0f} };
	float starRadius = 10.0f;
	float starLight[1][9]{ { 1.f, 1.f, 1.f,1.f, 1.f, 1.f,1.f, 1.f, 1.f} };
	GLfloat rotation = 100.f;
	float starColor[1][3] = { {1.0f, 1.0f , 1.0f}, };
}

namespace Bk {
	float starLocation[1][3]{ {0.0f, 0.0f , 0.0f} };
	float starRadius = 150.0f;
	float starLight[1][9]{ { 1.0f, 1.0f, 1.0f,1.0f, 1.0f, 1.0f,1.0f, 1.0f, 1.0f} };
	float starColor[1][3] = { {1.0f, 1.0f , 1.0f}, };
}

namespace Pl {
	// Localiza��o de 8 Planetas
	float planetlocations[8][3] = {
		{0.0f, 0.f, 597.0f}, //Mercurio
		{0.0f, 0.f, 748.0f}, // Venus
		{0.0f, 0.f, 889.0f}, // Terra
		{0.0f, 0.f, 1147.0f}, // Marte 
		{0.0f, 0.f, 1570.0f}, // Jupiter
		{0.0f, 0.f, 2150.0f}, //Saturno
		{0.0f, 0.f, 2590.0f}, // Urano
		{0.0f, 0.f, 2820.0f} //Neptuno
	};

	float planetDefaultlocations[8][3] = {
		{0.0f, 0.f, 597.0f}, //Mercurio
		{0.0f, 0.f, 748.0f}, // Venus
		{0.0f, 0.f, 889.0f}, // Terra
		{0.0f, 0.f, 1147.0f}, // Marte 
		{0.0f, 0.f, 1570.0f}, // Jupiter
		{0.0f, 0.f, 2150.0f}, //Saturno
		{0.0f, 0.f, 2590.0f}, // Urano
		{0.0f, 0.f, 2820.0f} //Neptuno
	};

	GLfloat rotation[8] = { 10.f,20.f,30.f,40.f,50.f,60.f,70.f,80.f };

	//Luz
	float planetLight[8][9]{ 
		{0.8f, 0.8f, 0.8f,0.8f, 0.8f, 0.8f,0.7f, 0.7f, 0.7f},
		{0.7f, 0.7f, 0.8f,0.7f, 0.7f, 0.7f,0.6f, 0.6f, 0.6f},
		{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
		{0.5f, 0.5f, 0.5f,0.5f, 0.5f, 0.5f,0.4f, 0.4f, 0.4f},
		{0.3f, 0.3f, 0.3f,0.4f, 0.4f, 0.4f,0.3f, 0.3f, 0.3f},
		{0.3f, 0.3f, 0.3f,0.3f, 0.3f, 0.3f,0.2f, 0.2f, 0.2f},
		{0.3f, 0.3f, 0.3f,0.2f, 0.2f, 0.2f,0.2f, 0.2f, 0.2f},
		{0.2f, 0.2f, 0.2f,0.1f, 0.1f, 0.1f,0.2f, 0.2f, 0.2f}
	};

	// Radius de 8 planetas
	float planetRadius[8] = {
		0.18f,//Mercurio
		0.44f,//Venus
		0.46f,//Terra
		0.24f,//Marte
		5.15f,//Jupiter
		3.0f,//Saturno
		1.86f,//Urano
		1.80f//Neptuno
	};

	// Velocidade de 8 planetas
	float planetSpeed[8] = {
		10.0f,
		5.2f,
		4.0f,
		2.3f,
		1.84f,
		2.0f,
		2.12f,
		2.22f
	};

	// Angulo de 8 planetas
	float planetAngle[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	// Store the distances to the star of the 6 spheres
	float planetDistance[8] = {
		597.0f,
		748.0f,
		889.0f,
		1147.0f,
		1570.0f,
		2150.0f,
		2590.0f,
		2820.0f
	}; // Distancia ao sol.
}
namespace Moon {
	float moonTransCenter[1][3] = { Pl::planetlocations[2][0], Pl::planetlocations[2][1], Pl::planetlocations[2][2] };
	// Localizacao de luas
	float moonlocations[1][3] = {
		{ moonTransCenter[0][0], moonTransCenter[0][1], moonTransCenter[0][2] + 30.0f}
	};

	float moonDefaultLocation[1][3] = {{ moonTransCenter[0][0], moonTransCenter[0][1], moonTransCenter[0][2] + 30.0f}};

	GLfloat rotation = 10.f;
	// Raio da lua
	float moonRadius[1] = { 0.1f };
	// Angulo da lua
	float moonAngle[1] = { 0.0f };
	float moonLight[1][9]{ {0.9f, 0.9f, 0.9f,0.95f, 0.95f, 0.95f,0.1f, 0.1f, 0.1f} };
	// distancia ao planeta
	float moonDistance[1] = { 30.0f };
	//velocidade da lua
	float moonSpeed[1] = { 7.0f };
}


SceneTexture::SceneTexture() {
	venus = ObjMesh::load("../media/Venus/venus.obj", true);
	saturn = ObjMesh::load("../media/Saturn/saturn3.obj", true);

	texSun = Texture::loadPixels("../media/texturas/2k_sun.jpg", sSun, tSun);
	texMercury = Texture::loadPixels("../media/texturas/2k_mercury.jpg", sMercury, tMercury);
	texVenus = Texture::loadPixels("../media/texturas/2k_venus_surface.jpg", sVenus, tVenus);
	texEarth = Texture::loadPixels("../media/texturas/2k_earth_daymap.jpg", sEarth, tEarth);
	texMars = Texture::loadPixels("../media/texturas/2k_mars.jpg", sMars, tMars);
	texJupiter = Texture::loadPixels("../media/texturas/2k_jupiter.jpg", sJupiter, tJupiter);
	texSaturn = Texture::loadPixels("../media/texturas/2k_saturn.jpg", sSaturn, tSaturn);
	texUranus = Texture::loadPixels("../media/texturas/2k_uranus.jpg", sUranus, tUranus);
	texNeptune = Texture::loadPixels("../media/texturas/2k_neptune.jpg", sNeptune, tNeptune);
	texMoon = Texture::loadPixels("../media/texturas/2k_moon.jpg", sMoon, tMoon);
	texSkyBox = Texture::loadPixels("../media/2k_stars_milky_way.jpg", sSkyBox, tSkyBox);
}

void SceneTexture::initScene()
{
    compileAndLinkShader();

    glEnable(GL_DEPTH_TEST);

	view = glm::lookAt(
		glm::vec3(camx, 1000.0f, camz), //Camera esta
		glm::vec3(0, 0, 0), //Esta a olhar para
		glm::vec3(1, 0, 1)  //Posicao da cabeca
	);


	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    angle = 0.0;
	glGenTextures(1, &textL);


}

void SceneTexture::update( float t ) { }

void SceneTexture::render()
{

	if (is2d) {
		view = glm::lookAt(
			glm::vec3(0.1f, 2500.f, 0.f), //Camera esta
			glm::vec3(0, 0, 0), //Esta a olhar para
			glm::vec3(0, 1, 0)  //Posicao da cabeca
		);
	}
	else {
		view = glm::lookAt(
			glm::vec3(camx, camz, 0.f), //Camera esta
			glm::vec3(0, 0, 0), //Esta a olhar para
			glm::vec3(0, 1, 0)  //Posicao da cabeca
		);
	}
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	prog.setUniform("Light.Position", glm::vec4(.0f, .0f, .0f, 1.0f));
	prog.setUniform("Light.Intensity", glm::vec3(1.f, 1.f, 1.f));

	calcPlanetLocations();
	calcMoonLocation();
	renderPlanet(St::starLocation[0],St::starLight[0],St::starRadius, (GLfloat)glfwGetTime(),St::rotation);
	textureLoad(texSun, sSun, tSun);
	setMatrices();
	venus->render();

	//Lua
	renderPlanet(Moon::moonlocations[0], Moon::moonLight[0], Moon::moonRadius[0], (GLfloat)glfwGetTime(),Moon::rotation);
	textureLoad(texMoon, sMoon, tMoon);
	setMatrices();
	venus->render();

	//Mercurio
	renderPlanet(Pl::planetlocations[0], Pl::planetLight[0], Pl::planetRadius[0], (GLfloat)glfwGetTime(), Pl::rotation[0]);
	textureLoad(texMercury, sMercury, tMercury);
	setMatrices();
	venus->render();

	//Venus
	renderPlanet(Pl::planetlocations[1], Pl::planetLight[1], Pl::planetRadius[1], (GLfloat)glfwGetTime(), Pl::rotation[1]);
	textureLoad(texVenus, sVenus, tVenus);
	setMatrices();
	venus->render();

	//Terra
	renderPlanet(Pl::planetlocations[2], Pl::planetLight[2], Pl::planetRadius[2], (GLfloat)glfwGetTime(), Pl::rotation[2]);
	textureLoad(texEarth, sEarth, tEarth);
	setMatrices();
	venus->render();

	//Marte
	renderPlanet(Pl::planetlocations[3], Pl::planetLight[3], Pl::planetRadius[3], (GLfloat)glfwGetTime(), Pl::rotation[3]);
	textureLoad(texMars, sMars, tMars);
	setMatrices();
	venus->render();

	//Jupiter
	renderPlanet(Pl::planetlocations[4], Pl::planetLight[4], Pl::planetRadius[4], (GLfloat)glfwGetTime(), Pl::rotation[4]);
	textureLoad(texJupiter, sJupiter, tJupiter);
	setMatrices();
	venus->render();

	//Saturno
	renderPlanet(Pl::planetlocations[5], Pl::planetLight[5], Pl::planetRadius[5], (GLfloat)glfwGetTime(), Pl::rotation[5]);
	textureLoad(texSaturn, sSaturn, tSaturn);
	setMatrices();
	saturn->render();

	//Urano
	renderPlanet(Pl::planetlocations[6], Pl::planetLight[6], Pl::planetRadius[6], (GLfloat)glfwGetTime(), Pl::rotation[6]);
	textureLoad(texUranus, sUranus, tUranus);
	setMatrices();
	venus->render();

	//Neptuno
	renderPlanet(Pl::planetlocations[7], Pl::planetLight[7], Pl::planetRadius[7], (GLfloat)glfwGetTime(), Pl::rotation[7]);
	textureLoad(texNeptune, sNeptune, tNeptune);
	setMatrices();
	venus->render();

	//Neptuno
	renderBK(Bk::starRadius);
	textureLoad(texSkyBox, sSkyBox, tSkyBox);
	setMatrices();
	venus->render();
	
}

void SceneTexture::renderPlanet(float sLoc[3],float sLi[9], float sR, GLfloat t,GLfloat rotation) {
	prog.setUniform("Material.Kd", sLi[0], sLi[1], sLi[2]);
	prog.setUniform("Material.Ks", sLi[3], sLi[4], sLi[5]);
	prog.setUniform("Material.Ka", sLi[6], sLi[7], sLi[8]);
	prog.setUniform("Material.Shininess", 100.0f);
	model = mat4(1.0f);
	model = glm::translate(model, glm::vec3(sLoc[0], sLoc[1], sLoc[2]));
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(sR, sR, sR));
	model = glm::rotate(model, glm::radians<float>(t* rotation), vec3(0,1,0));
	model = model * scale;
}

void SceneTexture::renderBK(float sR) {
	prog.setUniform("Material.Kd", 1.0f, 1.0f, 1.0f);
	prog.setUniform("Material.Ks", 1.0f, 1.0f, 1.0f);
	prog.setUniform("Material.Ka", 1.0f, 1.0f, 1.0f);
	prog.setUniform("Material.Shininess", 100.0f);
	model = mat4(1.0f);
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(sR, sR, sR));
	model = model * scale;
}

void SceneTexture::setMatrices()
{
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",glm::mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
    prog.setUniform("MVP", projection * mv);
}

void SceneTexture::resize(int w, int h)
{
    glViewport(0,0,w,h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(100.0f), 16.0f / 9.0f, 0.1f, 10000.0f);
}

void SceneTexture::compileAndLinkShader()
{
  try {
    prog.compileShader("shader/texture.vs");
    prog.compileShader("shader/texture.fs");
    prog.link();
    prog.use();
  } catch(GLSLProgramException & e) {
    cerr << e.what() << endl;
    exit( EXIT_FAILURE );
  }
}

void SceneTexture::textureLoad(GLubyte* data, int width, int height) {
	if (data != nullptr) {
		glBindTexture(GL_TEXTURE_2D, textL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);


	}
}

void SceneTexture::calcPlanetLocations() {
	if (paused)
		return;
	for (int i = 0; i < 8; i++)
	{
		Pl::planetAngle[i] += Pl::planetSpeed[i];
		while (Pl::planetAngle[i] > 360.0)
			Pl::planetAngle[i] -= 360.0;
		float tempAngle = (Pl::planetAngle[i] / 180.0f) * 3.14159f;
		Pl::planetlocations[i][0] = sin(tempAngle) * Pl::planetDistance[i];
		Pl::planetlocations[i][2] = cos(tempAngle) * Pl::planetDistance[i];
	}
}

void SceneTexture::calcMoonLocation() {
	if (paused)
		return;

	Moon::moonTransCenter[0][0] = Pl::planetlocations[2][0];
	Moon::moonTransCenter[0][1] = Pl::planetlocations[2][1];
	Moon::moonTransCenter[0][2] = Pl::planetlocations[2][2];


	Moon::moonAngle[0] += Moon::moonSpeed[0];

	while (Moon::moonAngle[0] > 360.0)
		Moon::moonAngle[0] -= 360.0;

	float tempAngle = (Moon::moonAngle[0] / 180.0f) * 3.14159f;
	Moon::moonlocations[0][0] = Moon::moonTransCenter[0][0] + sin(tempAngle) * Moon::moonDistance[0];
	Moon::moonlocations[0][2] = Moon::moonTransCenter[0][2] + cos(tempAngle) * Moon::moonDistance[0];
}