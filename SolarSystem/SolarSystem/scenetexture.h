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

	static bool paused,is2d;
	static GLfloat camx, camz;
	static glm::mat4 modelAux, viewAux, projectionAux;
	static void keyfunc(GLFWwindow*, int, int, int, int);

	void initScene();
	void update(float t);
	void render();
	void resize(int, int);
	void textureLoad(GLubyte*, int, int);
	void renderPlanet(float[3], float[9], float);
	void renderSun(float[3], float[9], float);
	void calcPlanetLocations();
	void calcMoonLocation();
};

#endif // SCENEPERFRAGMENT_H
