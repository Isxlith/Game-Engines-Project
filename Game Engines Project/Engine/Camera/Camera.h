#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Camera
{
public:
	Camera();
	~Camera();

	void SetPos(vec3 pos_);
	void SetRotation(float yaw_, float pitch_);

	inline mat4 GetView() const { return view; };
	inline mat4 GetPerspective() const { return perspective; };
	inline mat4 GetOrtho() const { return ortho; };
	inline vec3 getPos() const { return pos; };

private:
	void UpdateCameraVectors();
	vec3 pos;
	mat4 perspective, ortho, view;
	float fieldOfView;
	float yaw, pitch;
	float nearPlane, farPlane;
	vec3 forward, up, right, worldUp;
};

#endif