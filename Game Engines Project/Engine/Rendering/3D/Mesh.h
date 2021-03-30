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

struct SubMesh
{
	vector<Vertex> vertexList;
	vector<unsigned int> meshIndices;
	GLuint textureID;
};

class Mesh
{
public:
	Mesh(SubMesh& subMesh_, GLuint shaderProgram_);
	~Mesh();

	void Render(Camera* camera_, vector<mat4>& instances_);

private:
	void GenerateBuffers();
	GLuint VAO, VBO;
	SubMesh subMesh;
	GLuint shaderProgram;
	GLuint modelLocation, viewLocation, projectionLocation, textureLocation;

	GLuint cameraPos, lightPos, ambient, diffuse, specular, lightColour;
};

#endif