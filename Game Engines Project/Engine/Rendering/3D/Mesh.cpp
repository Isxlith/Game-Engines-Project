#include "Mesh.h"

Mesh::Mesh(vector<Vertex>& vertexList_, GLuint textureID_, GLuint shaderProgram_) : VAO(0), VBO(0), vertexList(vector<Vertex>()), shaderProgram(0), textureID(0), modelLocation(0), viewLocation(0), projectionLocation(0), textureLocation(0)
{
	vertexList = vertexList_;
	textureID = textureID_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	vertexList.clear();
}

void Mesh::Render(Camera* camera_, mat4 transform_)
{
	glUniform1i(textureLocation, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(camera_->GetPerspective()));

	glUniform3fv(cameraPos, 1, value_ptr(camera_->getPos()));
	glUniform3fv(lightPos, 1, value_ptr(camera_->listLightSources()[0]->GetPos()));
	glUniform1f(ambient, camera_->listLightSources()[0]->GetAmbient());
	glUniform1f(diffuse, camera_->listLightSources()[0]->GetDiffuse());
	glUniform1f(specular, camera_->listLightSources()[0]->GetSpecular());
	glUniform3fv(lightColour, 1, value_ptr(camera_->listLightSources()[0]->GetColour()));

	glBindVertexArray(VAO);
	glEnable(GL_DEPTH_TEST);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(transform_));
	glDrawArrays(GL_TRIANGLES, 0, vertexList.size());
	glBindVertexArray(0);
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex), &vertexList[0], GL_STATIC_DRAW);

	// Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	// Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	// Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoords));

	// Colour
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLocation = glGetUniformLocation(shaderProgram, "model");
	viewLocation = glGetUniformLocation(shaderProgram, "view");
	projectionLocation = glGetUniformLocation(shaderProgram, "projection");
	textureLocation = glGetUniformLocation(shaderProgram, "inputTexture");

	cameraPos = glGetUniformLocation(shaderProgram, "cameraPos");
	lightPos = glGetUniformLocation(shaderProgram, "light.lightPos");
	ambient = glGetUniformLocation(shaderProgram, "light.ambient");
	diffuse = glGetUniformLocation(shaderProgram, "light.diffuse");
	specular = glGetUniformLocation(shaderProgram, "light.specular");
	lightColour = glGetUniformLocation(shaderProgram, "light.lightColor");
}