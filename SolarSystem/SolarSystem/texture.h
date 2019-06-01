
#include "cookbookogl.h"
#include <string>

class Texture {
public:
	static unsigned char* loadPixels(const std::string& fName, int& w, int& h);
};