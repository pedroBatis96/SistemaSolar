#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

///*static*/

unsigned char *Texture::loadPixels(const std::string &fName, int & width, int & height) {
    int bytesPerPix;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(fName.c_str(), &width, &height, &bytesPerPix, 4);
    return data;
}
