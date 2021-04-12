#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../FX/LightSource.h"

using namespace glm;
using namespace std;

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
	inline vec3 GetPos() const { return pos; };

	void addLightSource(vec3 pos_, float ambient_, float diffuse_, float specular_, vec3 colour_);
	inline vector<LightSource*> listLightSources() { return lightSources; };

	void ProcessMouseMovement(vec2 offset_);
	void ProcessMouseZoom(int y_);

private:
	void UpdateCameraVectors();
	vec3 pos;
	mat4 perspective, ortho, view;
	float fieldOfView;
	float yaw, pitch;
	float nearPlane, farPlane;
	vec3 forward, up, right, worldUp;

	vector<LightSource*> lightSources;
};

#endif