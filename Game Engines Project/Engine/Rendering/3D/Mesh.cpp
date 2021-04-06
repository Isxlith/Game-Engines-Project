#include "Mesh.h"

Mesh::Mesh(SubMesh& subMesh_, GLuint shaderProgram_) : VAO(0), VBO(0), shaderProgram(0), modelLocation(0), viewLocation(0), projectionLocation(0), cameraPos(0), lightPos(0), ambient(0), diffuse(0), specular(0), lightColour(0), diffuseMap(0), matShininess(0), matTransparency(0), matAmbient(0), matDiffuse(0), matSpecular(0)
{
	subMesh = subMesh_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	
	if (subMesh.vertexList.size() > 0)
	{
		subMesh.vertexList.clear();
	}

	if (subMesh.meshIndices.size() > 0)
	{
		subMesh.meshIndices.clear();
	}
}

void Mesh::Render(Camera* camera_, vector<mat4>& instances_)
{
	glUniform1i(diffuseMap, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);

	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(camera_->GetPerspective()));

	// Light Uniforms
	glUniform3fv(cameraPos, 1, value_ptr(camera_->getPos()));
	glUniform3fv(lightPos, 1, value_ptr(camera_->listLightSources()[0]->GetPos()));
	glUniform1f(ambient, camera_->listLightSources()[0]->GetAmbient());
	glUniform1f(diffuse, camera_->listLightSources()[0]->GetDiffuse());
	glUniform1f(specular, camera_->listLightSources()[0]->GetSpecular());
	glUniform3fv(lightColour, 1, value_ptr(camera_->listLightSources()[0]->GetColour()));
	
	// Material Uniform
	glUniform1f(matShininess, subMesh.material.shininess);
	glUniform1f(matTransparency, subMesh.material.transparency);
	glUniform3fv(matAmbient, 1, value_ptr(subMesh.material.ambient));
	glUniform3fv(matDiffuse, 1, value_ptr(subMesh.material.diffuse));
	glUniform3fv(matSpecular, 1, value_ptr(subMesh.material.specular));

	glBindVertexArray(VAO);
	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < instances_.size(); i++)
	{
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	// Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	// Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	// Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoords));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLocation = glGetUniformLocation(shaderProgram, "model");
	viewLocation = glGetUniformLocation(shaderProgram, "view");
	projectionLocation = glGetUniformLocation(shaderProgram, "projection");

	// Light Uniform
	cameraPos = glGetUniformLocation(shaderProgram, "cameraPos");
	lightPos = glGetUniformLocation(shaderProgram, "light.lightPos");
	ambient = glGetUniformLocation(shaderProgram, "light.ambient");
	diffuse = glGetUniformLocation(shaderProgram, "light.diffuse");
	specular = glGetUniformLocation(shaderProgram, "light.specular");
	lightColour = glGetUniformLocation(shaderProgram, "light.lightColor");

	// Material Uniform
	diffuseMap = glGetUniformLocation(shaderProgram, "material.diffuseMap");
	matShininess = glGetUniformLocation(shaderProgram, "material.shininess");
	matTransparency = glGetUniformLocation(shaderProgram, "material.transparency");
	matAmbient = glGetUniformLocation(shaderProgram, "material.ambient");
	matDiffuse = glGetUniformLocation(shaderProgram, "material.diffuse");
	matSpecular = glGetUniformLocation(shaderProgram, "material.specular");
}