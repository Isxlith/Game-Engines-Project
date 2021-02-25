#include "Model.h"

Model::Model(GLuint shaderProgram_, vec3 pos_, float angle_, vec3 rotation_, vec3 scale_) : meshes(vector<Mesh*>()), shaderProgram(0), pos(vec3()), angle(0.0f), rotation(vec3(0.0f, 1.0f, 0.0f)), scale(vec3(1.0f))
{
	shaderProgram = shaderProgram_;
	pos = pos_;
	angle = angle_;
	rotation = rotation_;
	scale = scale_;
}

Model::~Model()
{
	if (meshes.size() > 0)
	{
		for (auto m : meshes)
		{
			delete m;
			m = nullptr;
		}
		meshes.clear();
	}
}

void Model::Render(Camera* camera_)
{
	// Tells openGL which shader program to use
	glUseProgram(shaderProgram);
	for (auto m : meshes)
	{
		m->Render(camera_, GetTransform());
	}
}

void Model::AddMesh(Mesh* mesh_)
{
	meshes.push_back(mesh_);
}

mat4 Model::GetTransform() const
{
	mat4 model;
	model = translate(model, pos);
	model = rotate(model, angle, rotation);
	model = glm::scale(model, scale);
	return model;
}

void Model::SetPos(vec3 pos_)
{
	pos = pos_;
}

void Model::SetRotation(vec3 rotation_)
{
	rotation = rotation_;
}

void Model::SetScale(vec3 scale_)
{
	scale = scale_;
}

void Model::SetAngle(float angle_)
{
	angle = angle_;
}