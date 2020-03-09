#include "Terrain.h"

float Terrain::SIZE = 800;
int Terrain::VERTEX_COUNT = 128;

Terrain::Terrain(int gridX, int gridZ, GLuint textureID) {
	this->x = gridX * SIZE; 
	this->z = gridZ * SIZE;
	generateTerrain();
	shaderID = LoadShaders("shaders/terrain.vert", "shaders/terrain.frag");
	this->textureID = textureID;
}
 
Terrain::~Terrain() {

}
void Terrain::draw() {
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBindVertexArray(vao);
	try {
		glDrawElements(GL_TRIANGLES, VERTEX_COUNT, GL_UNSIGNED_INT, 0);
	}
	catch (const std::exception & e) {
		std::cout << e.what() << "\n";
	}
}

void Terrain::update() {

}

void Terrain::generateTerrain() {
	int count = VERTEX_COUNT * VERTEX_COUNT;
	vertices = std::vector<float>(count * 3, 0);
	normals = std::vector<float>(count * 3, 0);
	textureCoords = std::vector<float>(count * 2, 0);
	indices = std::vector<unsigned int>(6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1), 0);
	int vertexPtr = 0;

	//initialize vertices
	for (int i = 0; i < VERTEX_COUNT; i++) {
		for (int j = 0; j < VERTEX_COUNT; j++) {
			//initialize vertices
			vertices[vertexPtr * 3] = -j / (VERTEX_COUNT - 1) * SIZE;
			vertices[vertexPtr * 3 + 1] = 0;
			vertices[vertexPtr * 3 + 2] = -i / (VERTEX_COUNT - 1) * SIZE;

			//initialize normals
			normals[vertexPtr * 3] = 0;
			normals[vertexPtr * 3 + 1] = 1;
			normals[vertexPtr * 3 + 2] = 0;

			//initialize texture coordinates
			textureCoords[vertexPtr * 2] = j / (VERTEX_COUNT - 1);
			textureCoords[vertexPtr * 2 + 1] = i / (VERTEX_COUNT - 1);
			
			//increment vertex pointer
			vertexPtr++;
		}
	}

	//initialize indicies
	int ptr = 0;
	for (int z = 0; z < VERTEX_COUNT - 1; z++) {
		for (int x = 0; x < VERTEX_COUNT - 1; x++) {
			unsigned int topleft = (z * VERTEX_COUNT) + x;
			unsigned int topright = topleft + 1;
			unsigned int botleft = ((z + 1) * VERTEX_COUNT) + x;
			unsigned int botright = botleft + 1;
			indices[ptr++] = topleft;
			indices[ptr++] = botleft;
			indices[ptr++] = topright;
			indices[ptr++] = topright;
			indices[ptr++] = botleft;
			indices[ptr++] = botright;
		}
	}
	loadVAO(vertices, textureCoords, normals, indices);
	//return loader.loadMultipleToVao(vertices, textureCoords, normals, indices);
	//return Model(1, 1);
}

void Terrain::loadVAO(std::vector<float> vertices, std::vector<float> textureCoords,
	std::vector<float> normals, std::vector<unsigned int> indices) {
	//GLuint vao;
	glGenVertexArrays(1, &vao);
	vaos.push_back(vao);
	glBindVertexArray(vao);

	//bind indices to vbo
	glGenBuffers(1, &vbo);
	vbos.push_back(vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(),
		indices.data(), GL_STATIC_DRAW);

	//bind positions to vbo1
	glGenBuffers(1, &vbo1);
	vbos.push_back(vbo1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * vertices.size(),
		vertices.data(), GL_STATIC_DRAW);
	//save to location = 0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//bind textureCoords to vbo2
	glGenBuffers(1, &vbo2);
	vbos.push_back(vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * textureCoords.size(),
		textureCoords.data(), GL_STATIC_DRAW);
	//save to location = 0
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//bind normals to vbo3
	glGenBuffers(1, &vbo3);
	vbos.push_back(vbo3);
	glBindBuffer(GL_ARRAY_BUFFER, vbo3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * normals.size(),
		normals.data(), GL_STATIC_DRAW);
	//save to location = 0
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//return Model();
}
