#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

struct Vertex
{
	vec3 pos;
	vec3 normal;
	vec2 textureCoords;
	vec3 colour; // temporary
};

class Mesh
{
public:
	Mesh(vector<Vertex>& vertexList_);
	~Mesh();

	void Render();

private:
	void GenerateBuffers();
	GLuint VAO, VBO;
	vector<Vertex> vertexList;
};

#endif