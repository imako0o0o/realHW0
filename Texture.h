#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "stb_image.h"

class Texture {

private:
	GLuint textureID;
	float shininess = 1;
	float reflectivity = 1;
public:
	Texture(const char* filename);
	GLuint getID();
	float getShininess();
	float getReflectivity();
	void setReflectivity(float r);
};

#endif