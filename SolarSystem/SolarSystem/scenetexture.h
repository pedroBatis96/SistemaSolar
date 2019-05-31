#ifndef SCENETEXTURE_H
#define SCENETEXTURE_H

#include "scene.h"
#include "glslprogram.h"

#include <glm.hpp>
#include "objmesh.h"
#include <GLFW\glfw3.h>

class SceneTexture : public Scene
{
private:
	GLSLProgram prog;



	std::unique_ptr<ObjMesh> sphere,sun,mercury,venus,earth,mars,jupiter,saturn,uranus,neptune,moon;
	GLubyte* texSun, * texMercury, * texVenus, * texEarth, * texMars, * texJupiter, * texSaturn, * texUranus, * texNeptune,* texMoon,* texSkyBox;
	GLint sSun, tSun,
		sMercury, tMercury,
		sVenus, tVenus,
		sEarth, tEarth,
		sMars, tMars,
		sJupiter, tJupiter,
		sSaturn, tSaturn,
		sUranus, tUranus,
		sNeptune, tNeptune,
		sMoon, tMoon,
		sSkyBox,tSkyBox;


	float angle;

	void setMatrices();
	void compileAndLinkShader();


public:
	SceneTexture();
	GLuint textL;

	//Planetas-------------------------------------
	static float planetlocations[8][3];
	static float planetDefaultlocations[8][3];
	static GLfloat planetRotation[8];
	//Luz
	static float planetLight[8][9];
	// Radius de 8 planetas
	static float planetRadius[8];
	static float planetSpeed[8];
	static float planetAngle[8];
	// Store the distances to the star of the 6 spheres
	static float planetDistance[8]; // Distancia ao sol.

	//Lua--------------------------------
	static float moonTransCenter[1][3];
	// Localizacao de luas
	static float moonlocations[1][3];
	static float moonDefaultLocation[1][3];
	static GLfloat moonRotation;
	// Raio da lua
	static float moonRadius[1];
	// Angulo da lua
	static float moonAngle[1];
	static float moonLight[1][9];
	// distancia ao planeta
	static float moonDistance[1];
	//velocidade da lua
	static float moonSpeed[1];

	//Background------------------------------------------------------------------------
	static float bkLocation[1][3];
	static float bkRadius;
	static float bkLight[1][9];
	static float bkColor[1][3];


	//Sol-------------------------------------------------------------------------------
	static float starLocation[1][3];
	static float starRadius;
	static float starLight[1][9];
	static GLfloat rotation;
	static float starColor[1][3];

	static bool paused,is2d,retry,isMenu;
	static GLfloat camx,camy, camz,eyex,eyey,eyez;
	static glm::mat4 modelAux, viewAux, projectionAux;
	static void keyfunc(GLFWwindow*, int, int, int, int);
	static int selected;

	void initScene();
	void update(float t);
	void render();
	void resize(int, int);
	void textureLoad(GLubyte*, int, int);
	void setDefaults();
	void renderBK(float);
	void renderPlanet(float[3], float[9], float, GLfloat, GLfloat);
	void calcPlanetLocations();
	void calcMoonLocation();
};

#endif // SCENEPERFRAGMENT_H
