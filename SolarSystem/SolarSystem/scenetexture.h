#ifndef SCENETEXTURE_H
#define SCENETEXTURE_H

#include "scene.h"
#include "glslprogram.h"
#include "plane.h"

#include <glm.hpp>
#include "objmesh.h"
#include <GLFW\glfw3.h>

/// Classe responsavel por tudo existente no Sistema Solar
class SceneTexture : public Scene
{
private:
	/// Plano responsavel pela exibicao do menu
	Plane menu;

	GLSLProgram prog;

	///Objeto responsavel por maior parte dos planetas
	std::unique_ptr<ObjMesh> venus;
	///Objeto responsavel Saturno
	std::unique_ptr<ObjMesh> saturn;
	///Objeto responsavel pelos asteróides
	std::unique_ptr<ObjMesh> asteroid;
	///Exemplar da variável que guarda uma textura
	GLubyte* texSun;
	GLubyte* texMercury, * texVenus, * texEarth, * texMars, * texJupiter, * texSaturn, * texUranus, * texNeptune,* texMoon,* texSkyBox, * texAbel, * texBlue, *texAsteroid;
	GLubyte* texmSun, * texmMercury, * texmVenus, * texmEarth, * texmMars, * texmJupiter, * texmSaturn, * texmUranus, * texmNeptune;
	GLint sSun, tSun,sMercury, tMercury,sVenus, tVenus,sEarth, tEarth,sMars, tMars,sJupiter, tJupiter,sSaturn, tSaturn,sUranus, tUranus,sNeptune, tNeptune,sMoon, tMoon,
		sSkyBox,tSkyBox,sAbel, tAbel,sBlue, tBlue,sAsteroid, tAsteroid;
	GLint smSun, tmSun, smMercury, tmMercury, smVenus, tmVenus, smEarth, tmEarth, smMars, tmMars, smJupiter, tmJupiter, smSaturn, tmSaturn, smUranus, tmUranus, smNeptune, tmNeptune;
		

	
	float angle;

	/// Função responsável pelo set das Matrizes, após alterações ao model ou texturas
	void setMatrices();
	/// Função responsável pela compilação de shaders
	void compileAndLinkShader();
	/// Função responsável pelo load das texturas
	void textureLoad(GLubyte*, int, int);
	/// Função responsável pelo calculo da posição dos planetas
	void calcPlanetLocations();
	/// Função responsável pelo cálculo da posição da Lua
	void calcMoonLocation();
public:
	SceneTexture();
	///Variavel onde as texturas sao geradas
	GLuint textL;

	//Planetas-------------------------------------
	///Variavel responsavel por guardar a localizacao do planeta
	static float planetlocations[8][3];
	///Variavel responsavel por guardar a localizacao default do planeta
	static float planetDefaultlocations[8][3];
	///Variavel responsavel por guardar a velocidade de rotacao do planeta
	static GLfloat planetRotation[8];
	///Variavel responsavel por guardar os atributos de reflexao do planeta
	static float planetLight[8][9];
	///Variavel responsavel por guardar quanto o planeta vai escalar
	static float planetRadius[8];	
	///Variavel responsavel por guardar a velocidade de translacao do planeta
	static float planetSpeed[8];
	///Variavel responsavel por guardar o angulo de translacao onde o planeta se encontra
	static float planetAngle[8];
	///Variavel responsavel por guardar a distancia ao sol ao qual o planeta se encontra
	static float planetDistance[8];				

	//Asteroides-------------------------------------
	///Variavel responsavel por guardar a localizacao dos asteroides
	static float asteroidLocations[32][3];
	///Variavel responsavel por guardar a localizacao default dos asteroides
	static float asteroidDefaultLocations[32][3];
	///Variavel responsavel por guardar a velocidade de rotacao dos planetas
	static GLfloat asteroidRotation[32];
	///Variavel responsavel por guardar a reflexao dos asteroides
	static float asteroidLight[32][9];
	///Variavel responsavel por guardar o quanto os asteroides vao escalar
	static float asteroidRadius[32];
	///Variavel responsavel por guardar a velocidade de translacao do planeta
	static float asteroidSpeed[32];	
	///Variavel responsavel por guardar o angulo a que o asteroide se encontra
	static float asteroidAngle[32];
	///Variavel responsavel por guardar a distancia dos asteroides ao sol
	static float asteroidDistance[32];				

	//Lua--------------------------------
	///Variavel responsavel para saber o centro de gravidade da lua
	static float moonTransCenter[1][3];
	///Variavel responsavel por guardar a localizacao das luas
	static float moonlocations[1][3];
	///Variavel responsavel por guardar a localizacao default das luas
	static float moonDefaultLocation[1][3];
	///Variavel responsavel por guardar a velocidade de rotacao da lua
	static GLfloat moonRotation;
	///Variavel responsavel por guardar o raio da lua
	static float moonRadius[1];
	///Variavel responsavel por guardar o angulo de translacao da lua
	static float moonAngle[1];
	///Variavel responsavel por guardar a reflexao da lua
	static float moonLight[1][9];
	///Variavel responsavel por guardar a distancia ao centro de translacao
	static float moonDistance[1];
	///Variavel responsavel por guardar a velocidade da lua
	static float moonSpeed[1];

	//Background------------------------------------------------------------------------
	///Variavel responsavel por guardar a localizacao do centro do background
	static float bkLocation[1][3];
	///Variavel responsavel por guardar o raio do background
	static float bkRadius;
	///Variavel responsavel por guardar a luz reflexao do material
	static float bkLight[1][9];

	//Sol-------------------------------------------------------------------------------
	///Variavel responsavel por guardar a localizacao do centro do Sol
	static float starLocation[1][3];
	///Variavel responsavel por guardar o raio do Sol
	static float starRadius;
	///Variavel responsavel por guardar a reflexao do Sol
	static float starLight[1][9];
	///Variavel responsavel por guardar a rotacao do Sol
	static GLfloat rotation;

	static bool paused,is2d,retry,isMenu,isTroll;
	static GLfloat camx,camy, camz,eyex,eyey,eyez;
	
	static int selected;

	///Funcionalidades das teclas
	static void keyfunc(GLFWwindow*, int, int, int, int);
	///Inicializacao da cena
	void initScene();
	///Atualizacao da cena
	void update(float t);
	///Main loop da renderizacao
	void render();
	///Alteracao do tamanho do viewport
	void resize(int, int);
	///Renderizacao do background
	void renderBK(float);
	///Renderizacao do menu
	void renderMenu(int);
	///Renderizacao do planeta, onde e efetuada a translacao, rotacao e escalagem
	void renderPlanet(float[3], float[9], float, GLfloat, GLfloat);
};

#endif // SCENEPERFRAGMENT_H
