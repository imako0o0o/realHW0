#ifndef _TERRAIN_H_
#define _TERRAIN_H_

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
#include "Object.h"
#include "shader.h"
#include "Texture.h"

class Terrain : public Object {

private:
	static float SIZE;
	static int VERTEX_COUNT;
	std::vector<GLuint> vaos;
	GLuint vao, vbo, vbo1, vbo2, vbo3, vbo4;
	std::vector<GLuint> vbos;
	float x, z;
	//Model terrainModel;
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> textureCoords;
	std::vector<unsigned int> indices;
	GLuint shaderID;
	GLuint textureID;
	//Loader loader;
public: 
	Terrain(int gridX, int gridZ, GLuint textureID);
	~Terrain();

	void generateTerrain();
	void loadVAO(std::vector<float> vertices, std::vector<float> textureCoords,
		std::vector<float>normals, std::vector<unsigned int> indices);
	void draw();
	void update();

};
#endif