#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Camera/Camera.h"

using namespace std;
using namespace glm;

struct Vertex
{
	vec3 pos;
	vec3 normal;
	vec2 textureCoords;
	vec3 colour;
};

class Mesh
{
public:
	Mesh(vector<Vertex>& vertexList_, GLuint shaderProgram_);
	~Mesh();

	void Render(Camera* camera_, mat4 transform_);

private:
	void GenerateBuffers();
	GLuint VAO, VBO;
	vector<Vertex> vertexList;
	GLuint shaderProgram;
	GLuint modelLocation, viewLocation, projectionLocation;
};

#endif