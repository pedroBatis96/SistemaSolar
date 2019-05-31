#include "scenetexture.h"
#include "texture.h"
#include "stb/stb_image.h"

#include <iostream>
using std::endl;
using std::cerr;

#include <gtc/matrix_transform.hpp>
using glm::vec3;
using glm::mat4;

bool SceneTexture::paused = false, SceneTexture::is2d = false , SceneTexture::isMenu = false , SceneTexture::retry = false;
int SceneTexture::selected = 0;
GLFWwindow* window;
mat4 translate, scale,rotate;
GLfloat SceneTexture::camx = 2500.0f, SceneTexture::camy = 500.0f, SceneTexture::camz = 0.0f, SceneTexture::eyex = 0.0f, SceneTexture::eyey = 0.0f, SceneTexture::eyez = 0.0f;
glm::mat4 modelAux, viewAux, projectionAux;
float x = 0,xplus = 100;


//Planetas-------------------------------------
float SceneTexture::planetlocations[8][3] = {
	{0.0f, 0.f, 597.0f}, //Mercurio
	{0.0f, 0.f, 748.0f}, // Venus
	{0.0f, 0.f, 889.0f}, // Terra
	{0.0f, 0.f, 1147.0f}, // Marte 
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
//Luz
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
// Radius de 8 planetas
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
// Velocidade de 8 planetas
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
// Angulo de 8 planetas
float SceneTexture::planetAngle[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
// Store the distances to the star of the 6 spheres
float SceneTexture::planetDistance[8] = {
	597.0f,
	748.0f,
	889.0f,
	1147.0f,
	1570.0f,
	2150.0f,
	2590.0f,
	2820.0f
}; // Distancia ao sol.

//Lua--------------------------------
float SceneTexture::moonTransCenter[1][3] = { SceneTexture::planetlocations[2][0], SceneTexture::planetlocations[2][1], SceneTexture::planetlocations[2][2] };
// Localizacao de luas
float SceneTexture::moonlocations[1][3] = { { moonTransCenter[0][0], moonTransCenter[0][1], moonTransCenter[0][2] + 30.0f} };
float SceneTexture::moonDefaultLocation[1][3] = { { moonTransCenter[0][0], moonTransCenter[0][1], moonTransCenter[0][2] + 30.0f} };
GLfloat SceneTexture::moonRotation = 10.f;
// Raio da lua
float SceneTexture::moonRadius[1] = { 0.1f };
// Angulo da lua
float SceneTexture::moonAngle[1] = { 0.0f };
float SceneTexture::moonLight[1][9]{ {0.9f, 0.9f, 0.9f,0.95f, 0.95f, 0.95f,0.1f, 0.1f, 0.1f} };
// distancia ao planeta
float SceneTexture::moonDistance[1] = { 30.0f };
//velocidade da lua
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
		glm::vec3(camx, camy, camz), //Camera esta
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
	renderPlanet(SceneTexture::starLocation[0],SceneTexture::starLight[0],SceneTexture::starRadius, (GLfloat)glfwGetTime(),SceneTexture::rotation);
	textureLoad(texSun, sSun, tSun);
	setMatrices();
	venus->render();

	//Lua
	renderPlanet(SceneTexture::moonlocations[0], SceneTexture::moonLight[0], SceneTexture::moonRadius[0], (GLfloat)glfwGetTime(),SceneTexture::moonRotation);
	textureLoad(texMoon, sMoon, tMoon);
	setMatrices();
	venus->render();

	//Mercurio
	renderPlanet(SceneTexture::planetlocations[0], SceneTexture::planetLight[0], SceneTexture::planetRadius[0], (GLfloat)glfwGetTime(), SceneTexture::planetRotation[0]);
	textureLoad(texMercury, sMercury, tMercury);
	setMatrices();
	venus->render();

	//Venus
	renderPlanet(SceneTexture::planetlocations[1], SceneTexture::planetLight[1], SceneTexture::planetRadius[1], (GLfloat)glfwGetTime(), SceneTexture::planetRotation[1]);
	textureLoad(texVenus, sVenus, tVenus);
	setMatrices();
	venus->render();

	//Terra
	renderPlanet(SceneTexture::planetlocations[2], SceneTexture::planetLight[2], SceneTexture::planetRadius[2], (GLfloat)glfwGetTime(), SceneTexture::planetRotation[2]);
	textureLoad(texEarth, sEarth, tEarth);
	setMatrices();
	venus->render();

	//Marte
	renderPlanet(SceneTexture::planetlocations[3], SceneTexture::planetLight[3], SceneTexture::planetRadius[3], (GLfloat)glfwGetTime(), SceneTexture::planetRotation[3]);
	textureLoad(texMars, sMars, tMars);
	setMatrices();
	venus->render();

	//Jupiter
	renderPlanet(SceneTexture::planetlocations[4], SceneTexture::planetLight[4], SceneTexture::planetRadius[4], (GLfloat)glfwGetTime(), SceneTexture::planetRotation[4]);
	textureLoad(texJupiter, sJupiter, tJupiter);
	setMatrices();
	venus->render();

	//Saturno
	renderPlanet(SceneTexture::planetlocations[5], SceneTexture::planetLight[5], SceneTexture::planetRadius[5], (GLfloat)glfwGetTime(), SceneTexture::planetRotation[5]);
	textureLoad(texSaturn, sSaturn, tSaturn);
	setMatrices();
	saturn->render();

	//Urano
	renderPlanet(SceneTexture::planetlocations[6], SceneTexture::planetLight[6], SceneTexture::planetRadius[6], (GLfloat)glfwGetTime(), SceneTexture::planetRotation[6]);
	textureLoad(texUranus, sUranus, tUranus);
	setMatrices();
	venus->render();

	//Neptuno
	renderPlanet(SceneTexture::planetlocations[7], SceneTexture::planetLight[7], SceneTexture::planetRadius[7], (GLfloat)glfwGetTime(), SceneTexture::planetRotation[7]);
	textureLoad(texNeptune, sNeptune, tNeptune);
	setMatrices();
	venus->render();

	//Background
	renderBK(SceneTexture::bkRadius);
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

void SceneTexture::setDefaults() {
	
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
		SceneTexture::planetAngle[i] += SceneTexture::planetSpeed[i];
		while (SceneTexture::planetAngle[i] > 360.0)
			SceneTexture::planetAngle[i] -= 360.0;
		float tempAngle = (SceneTexture::planetAngle[i] / 180.0f) * 3.14159f;
		SceneTexture::planetlocations[i][0] = sin(tempAngle) * SceneTexture::planetDistance[i];
		SceneTexture::planetlocations[i][2] = cos(tempAngle) * SceneTexture::planetDistance[i];
	}
}

void SceneTexture::calcMoonLocation() {
	if (paused)
		return;

	SceneTexture::moonTransCenter[0][0] = SceneTexture::planetlocations[2][0];
	SceneTexture::moonTransCenter[0][1] = SceneTexture::planetlocations[2][1];
	SceneTexture::moonTransCenter[0][2] = SceneTexture::planetlocations[2][2];


	SceneTexture::moonAngle[0] += SceneTexture::moonSpeed[0];

	while (SceneTexture::moonAngle[0] > 360.0)
		SceneTexture::moonAngle[0] -= 360.0;

	float tempAngle = (SceneTexture::moonAngle[0] / 180.0f) * 3.14159f;
	SceneTexture::moonlocations[0][0] = SceneTexture::moonTransCenter[0][0] + sin(tempAngle) * SceneTexture::moonDistance[0];
	SceneTexture::moonlocations[0][2] = SceneTexture::moonTransCenter[0][2] + cos(tempAngle) * SceneTexture::moonDistance[0];
}