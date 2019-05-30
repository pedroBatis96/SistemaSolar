
#include "cookbookogl.h"
#include <string>

class Texture {
public:
	static GLuint loadTexture(const std::string& fName);
	static GLuint loadCubeMap(const std::string& baseName);
	static unsigned char* loadPixels(const std::string& fName, int& w, int& h);
	/*static GLuint loadTexture(unsigned char*, int, int);
    static unsigned char* loadPixels( const std::string & fName, int & w, int & h );*/
};