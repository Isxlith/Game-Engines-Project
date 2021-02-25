#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

class Model
{
public:
	Model(GLuint shaderProgram_, vec3 pos_ = vec3(), float angle_ = 0.0f, vec3 rotation_ = vec3(0.0f, 1.0f, 0.0f), vec3 scale_ = vec3(1.0f));
	~Model();

	void Render(Camera* camera_);
	void AddMesh(Mesh* mesh_);

	inline vec3 GetPos() const { return pos; };
	inline float GetAngle() const { return angle; };
	inline vec3 GetRotation() const { return rotation; };
	inline vec3 GetScale() const { return scale; };

	void SetPos(vec3 pos_);
	void SetAngle(float angle_);
	void SetRotation(vec3 rotation_);
	void SetScale(vec3 scale_);

private:
	vector<Mesh*> meshes;
	GLuint shaderProgram;

	vec3 pos;
	float angle;
	vec3 rotation;
	vec3 scale;
	mat4 GetTransform() const;
};

#endif