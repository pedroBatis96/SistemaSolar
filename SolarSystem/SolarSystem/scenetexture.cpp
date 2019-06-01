#include "scenetexture.h"
#include "texture.h"
#include "stb/stb_image.h"

#include <iostream>
using std::endl;
using std::cerr;

#include <gtc/matrix_transform.hpp>
using glm::vec3;
using glm::mat4;

bool SceneTexture::paused = false, SceneTexture::is2d = false, SceneTexture::isMenu = false,
SceneTexture::retry = false, SceneTexture::isTroll = false;
int SceneTexture::selected = 0;
GLFWwindow* window;
mat4 translate, scale,rotate;
GLfloat SceneTexture::camx = 2500.0f, SceneTexture::camy = 500.0f, SceneTexture::camz = 0.0f,
SceneTexture::eyex = 0.0f, SceneTexture::eyey = 0.0f, SceneTexture::eyez = 0.0f;
glm::mat4 modelAux, viewAux, projectionAux;
float x = 0,xplus = 100;


//Planetas-------------------------------------
float SceneTexture::planetlocations[8][3] = {
	{0.0f, 0.f, 597.0f}, //Mercurio
	{0.0f, 0.f, 748.0f}, // Venus
	{0.0f, 0.f, 889.0f}, // Terra
	{0.0f, 0.f, 1047.0f}, // Marte 
	{0.0f, 0.f, 1570.0f}, // Jupiter
	{0.0f, 0.f, 2150.0f}, //Saturno
	{0.0f, 0.f, 2590.0f}, // Urano
	{0.0f, 0.f, 2820.0f} //Neptuno
};
float SceneTexture::planetDefaultlocations[8][3] = {
	{0.0f, 0.f, 597.0f}, //Mercurio
	{0.0f, 0.f, 748.0f}, // Venus
	{0.0f, 0.f, 889.0f}, // Terra
	{0.0f, 0.f, 1147.0f}, // Marte 
	{0.0f, 0.f, 1570.0f}, // Jupiter
	{0.0f, 0.f, 2150.0f}, //Saturno
	{0.0f, 0.f, 2590.0f}, // Urano
	{0.0f, 0.f, 2820.0f} //Neptuno
};
GLfloat SceneTexture::planetRotation[8] = { 10.f,20.f,30.f,40.f,50.f,60.f,70.f,80.f };
float SceneTexture::planetLight[8][9]{
	{0.8f, 0.8f, 0.8f,0.8f, 0.8f, 0.8f,0.7f, 0.7f, 0.7f},
	{0.7f, 0.7f, 0.8f,0.7f, 0.7f, 0.7f,0.6f, 0.6f, 0.6f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.5f, 0.5f, 0.5f,0.5f, 0.5f, 0.5f,0.4f, 0.4f, 0.4f},
	{0.3f, 0.3f, 0.3f,0.4f, 0.4f, 0.4f,0.3f, 0.3f, 0.3f},
	{0.3f, 0.3f, 0.3f,0.3f, 0.3f, 0.3f,0.2f, 0.2f, 0.2f},
	{0.3f, 0.3f, 0.3f,0.2f, 0.2f, 0.2f,0.2f, 0.2f, 0.2f},
	{0.2f, 0.2f, 0.2f,0.1f, 0.1f, 0.1f,0.2f, 0.2f, 0.2f}
};
float SceneTexture::planetRadius[8] = {
	0.18f,//Mercurio
	0.44f,//Venus
	0.46f,//Terra
	0.24f,//Marte
	5.15f,//Jupiter
	3.0f,//Saturno
	1.86f,//Urano
	1.80f//Neptuno
};
float SceneTexture::planetSpeed[8] = {
	10.0f,
	5.2f,
	4.0f,
	2.3f,
	1.84f,
	2.0f,
	2.12f,
	2.22f
};
float SceneTexture::planetAngle[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
float SceneTexture::planetDistance[8] = {
	597.0f,
	748.0f,
	889.0f,
	1047.0f,
	1570.0f,
	2150.0f,
	2590.0f,
	2820.0f
}; // Distancia ao sol.

//Asteroides-------------------------------------
float SceneTexture::asteroidLocations[32][3] = {
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},  
	{0.0f, 0.f, 1247.0f}, 
	{0.0f, 0.f, 1247.0f}, 
	{0.0f, 0.f, 1247.0f}, 
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f},
	{0.0f, 0.f, 1247.0f}
};
float SceneTexture::asteroidDefaultLocations[32][3] = {
{0.0f, 0.f, 1247.0f},
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{0.0f,  0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{0.0f, 0.f, 1247.0f},
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{0.0f,  0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f },
{ 0.0f, 0.f, 1247.0f }
};
GLfloat SceneTexture::asteroidRotation[32] = { 10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f };
float SceneTexture::asteroidLight[32][9]{
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f},
	{0.6f, 0.6f, 0.6f,0.6f, 0.6f, 0.6f,0.5f, 0.5f, 0.5f}
};
float SceneTexture::asteroidRadius[32] = {
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f,
	6.0f
};
float SceneTexture::asteroidSpeed[32] = {
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f
};
float SceneTexture::asteroidAngle[32] = {
	11.25f, 22.5f, 33.75f, 45.5f, 56.75f, 68.0f, 79.25f, 90.5f, 101.75f, 113.0f, 124.25f, 135.5f, 146.75f, 158.0f, 169.25f, 180.5f,
	191.75f, 203.0f, 214.25f, 225.5f, 236.75f, 248.0f, 259.25f, 270.5f, 281.75f, 293.0f, 304.25f, 315.5f, 326.75f, 338.0f, 339.25f, 350.5f
};
float SceneTexture::asteroidDistance[32] = {
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f,
	1247.0f
};


//Lua--------------------------------
float SceneTexture::moonTransCenter[1][3] = { SceneTexture::planetlocations[2][0], SceneTexture::planetlocations[2][1], SceneTexture::planetlocations[2][2] };
float SceneTexture::moonlocations[1][3] = { { moonTransCenter[0][0], moonTransCenter[0][1], moonTransCenter[0][2] + 30.0f} };
float SceneTexture::moonDefaultLocation[1][3] = { { moonTransCenter[0][0], moonTransCenter[0][1], moonTransCenter[0][2] + 30.0f} };
GLfloat SceneTexture::moonRotation = 10.f;
float SceneTexture::moonRadius[1] = { 0.1f };
float SceneTexture::moonAngle[1] = { 0.0f };
float SceneTexture::moonLight[1][9]{ {0.9f, 0.9f, 0.9f,0.95f, 0.95f, 0.95f,0.1f, 0.1f, 0.1f} };
float SceneTexture::moonDistance[1] = { 30.0f };
float SceneTexture::moonSpeed[1] = { 100.0f };

//Background------------------------------------------------------------------------
float SceneTexture::bkLocation[1][3]{ {0.0f, 0.0f , 0.0f} };
float SceneTexture::bkRadius = 150.0f;
float SceneTexture::bkLight[1][9]{ { 1.0f, 1.0f, 1.0f,1.0f, 1.0f, 1.0f,1.0f, 1.0f, 1.0f} };
float SceneTexture::bkColor[1][3] = { {1.0f, 1.0f , 1.0f}, };


//Sol-------------------------------------------------------------------------------
float SceneTexture::starLocation[1][3]{ {0.0f, 0.0f , 0.0f} };
float SceneTexture::starRadius = 10.0f;
float SceneTexture::starLight[1][9]{ { 1.f, 1.f, 1.f,1.f, 1.f, 1.f,1.f, 1.f, 1.f} };
GLfloat SceneTexture::rotation = 100.f;
float SceneTexture::starColor[1][3] = { {1.0f, 1.0f , 1.0f}, };

SceneTexture::SceneTexture() {
	venus = ObjMesh::load("../media/objects/venus.obj", true);
	saturn = ObjMesh::load("../media/objects/saturn3.obj", true);
	asteroid = ObjMesh::load("../media/objects/asteroid.obj", true);

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
	texSkyBox = Texture::loadPixels("../media/texturas/2k_stars_milky_way.jpg", sSkyBox, tSkyBox);
	texAbel = Texture::loadPixels("../media/texturas/Abel.jpg", sAbel, tAbel);
	texBlue = Texture::loadPixels("../media/texturas/bluescreen.png", sBlue, tBlue);
	texAsteroid = Texture::loadPixels("../media/texturas/2k_asteroid.jpg", sAsteroid, tAsteroid);
}

void SceneTexture::initScene()
{
    compileAndLinkShader();

    glEnable(GL_DEPTH_TEST);

	view = glm::lookAt(
		glm::vec3(camx, camy, camz), //Camera esta
		glm::vec3(0, 0, 0), //Esta a olhar para
		glm::vec3(1, 0, 1)  //Posicao da cabeca
	);
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
			glm::vec3(camx, camy, camz), //Camera esta
			glm::vec3(eyex,eyey,eyez), //Esta a olhar para
			glm::vec3(0, 1, 0)  //Posicao da cabeca
		);
	}
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	prog.setUniform("Light.Position", glm::vec4(.0f, .0f, .0f, 1.0f));
	prog.setUniform("Light.Intensity", glm::vec3(1.f, 1.f, 1.f));

	calcPlanetLocations();
	calcMoonLocation();
	renderPlanet(starLocation[0],starLight[0],starRadius, (GLfloat)glfwGetTime(),rotation);
	if (!isTroll) {
		textureLoad(texSun, sSun, tSun);
	}
	else {
		textureLoad(texAbel, sAbel, tAbel);
	}
	setMatrices();
	venus->render();

	//Lua
	renderPlanet(moonlocations[0], moonLight[0], moonRadius[0], (GLfloat)glfwGetTime(),moonRotation);
	textureLoad(texMoon, sMoon, tMoon);
	setMatrices();
	venus->render();

	//Mercurio
	renderPlanet(planetlocations[0], planetLight[0], planetRadius[0], (GLfloat)glfwGetTime(), planetRotation[0]);
	textureLoad(texMercury, sMercury, tMercury);
	setMatrices();
	venus->render();

	//Venus
	renderPlanet(planetlocations[1], planetLight[1], planetRadius[1], (GLfloat)glfwGetTime(), planetRotation[1]);
	textureLoad(texVenus, sVenus, tVenus);
	setMatrices();
	venus->render();

	//Terra
	renderPlanet(planetlocations[2], planetLight[2], planetRadius[2], (GLfloat)glfwGetTime(), planetRotation[2]);
	textureLoad(texEarth, sEarth, tEarth);
	setMatrices();
	venus->render();

	//Marte
	renderPlanet(planetlocations[3], planetLight[3], planetRadius[3], (GLfloat)glfwGetTime(), planetRotation[3]);
	textureLoad(texMars, sMars, tMars);
	setMatrices();
	venus->render();

	//Jupiter
	renderPlanet(planetlocations[4], planetLight[4], planetRadius[4], (GLfloat)glfwGetTime(), planetRotation[4]);
	textureLoad(texJupiter, sJupiter, tJupiter);
	setMatrices();
	venus->render();

	//Saturno
	renderPlanet(planetlocations[5], planetLight[5], planetRadius[5], (GLfloat)glfwGetTime(), planetRotation[5]);
	textureLoad(texSaturn, sSaturn, tSaturn);
	setMatrices();
	saturn->render();

	//Urano
	renderPlanet(planetlocations[6], planetLight[6], planetRadius[6], (GLfloat)glfwGetTime(), planetRotation[6]);
	textureLoad(texUranus, sUranus, tUranus);
	setMatrices();
	venus->render();

	//Neptuno
	renderPlanet(planetlocations[7], planetLight[7], planetRadius[7], (GLfloat)glfwGetTime(), planetRotation[7]);
	textureLoad(texNeptune, sNeptune, tNeptune);
	setMatrices();
	venus->render();

	if (!isMenu) {
		for (int i = 0; i < 32; i++) {
			renderPlanet(asteroidLocations[i], asteroidLight[i], asteroidRadius[i], (GLfloat)glfwGetTime(), asteroidRotation[i]);
			textureLoad(texAsteroid, sAsteroid, tAsteroid);
			setMatrices();
			asteroid->render();
		}
	}

	//Background
	renderBK(bkRadius);
	if(!isTroll)
		textureLoad(texSkyBox, sSkyBox, tSkyBox);
	else
		textureLoad(texBlue, sBlue, tBlue);
	setMatrices();
	venus->render();
	
}

void SceneTexture::renderPlanet(float sLoc[3],float sLi[9], float sR, GLfloat t,GLfloat rotation) {
	if (paused) {
		prog.setUniform("Material.Kd", sLi[0], sLi[1], sLi[2]);
		prog.setUniform("Material.Ks", sLi[3], sLi[4], sLi[5]);
		prog.setUniform("Material.Ka", sLi[6], sLi[7], sLi[8]);
		prog.setUniform("Material.Shininess", 50.0f);
		model = mat4(1.0f);
		model = glm::translate(model, glm::vec3(sLoc[0], sLoc[1], sLoc[2]));
		scale = glm::scale(glm::mat4(1.0f), glm::vec3(sR, sR, sR));
		model = model * scale;
	}
	else {
		prog.setUniform("Material.Kd", sLi[0], sLi[1], sLi[2]);
		prog.setUniform("Material.Ks", sLi[3], sLi[4], sLi[5]);
		prog.setUniform("Material.Ka", sLi[6], sLi[7], sLi[8]);
		prog.setUniform("Material.Shininess", 50.0f);
		model = mat4(1.0f);
		model = glm::translate(model, glm::vec3(sLoc[0], sLoc[1], sLoc[2]));
		scale = glm::scale(glm::mat4(1.0f), glm::vec3(sR, sR, sR));
		model = glm::rotate(model, glm::radians<float>(t * rotation), vec3(0, 1, 0));
		model = model * scale;
	}
}

void SceneTexture::renderBK(float sR) {
	if (!isTroll) {
		prog.setUniform("Light.Intensity", glm::vec3(5.f, 5.f, 5.f));
	}
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
	}
}

void SceneTexture::calcPlanetLocations() {
	if (paused)
		return;
	for (int i = 0; i < 8; i++)
	{
		planetAngle[i] += planetSpeed[i];
		while (planetAngle[i] > 360.0)
			planetAngle[i] -= 360.0;
		float tempAngle = (planetAngle[i] / 180.0f) * 3.14159f;
		planetlocations[i][0] = sin(tempAngle) * planetDistance[i];
		planetlocations[i][2] = cos(tempAngle) * planetDistance[i];
	}

	for (int i = 0; i < 32; i++)
	{
		asteroidAngle[i] += asteroidSpeed[i];
		while (asteroidAngle[i] > 360.0)
			asteroidAngle[i] -= 360.0;
		float tempAngle = (asteroidAngle[i] / 180.0f) * 3.14159f;
		asteroidLocations[i][0] = sin(tempAngle) * asteroidDistance[i];
		asteroidLocations[i][2] = cos(tempAngle) * asteroidDistance[i];
	}
}

void SceneTexture::calcMoonLocation() {
	if (paused)
		return;

	moonTransCenter[0][0] = planetlocations[2][0];
	moonTransCenter[0][1] = planetlocations[2][1];
	moonTransCenter[0][2] = planetlocations[2][2];


	moonAngle[0] += moonSpeed[0];

	while (moonAngle[0] > 360.0)
		moonAngle[0] -= 360.0;

	float tempAngle = (moonAngle[0] / 180.0f) * 3.14159f;
	moonlocations[0][0] = moonTransCenter[0][0] + sin(tempAngle) * moonDistance[0];
	moonlocations[0][2] = moonTransCenter[0][2] + cos(tempAngle) * moonDistance[0];
}