#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../FX/LightSource.h"
#include "../Math/Frustum.h"

using namespace glm;
using namespace std;

class Camera
{
public:
	Camera();
	~Camera();

	void addLightSource(vec3 pos_, float ambient_, float diffuse_, float specular_, vec3 colour_);
	
	void ProcessMouseMovement(vec2 offset_);
	void ProcessMouseZoom(int y_);

	inline mat4 GetView() const { return view; };
	inline mat4 GetPerspective() const { return perspective; };
	inline mat4 GetOrtho() const { return ortho; };
	inline vec3 GetPos() const { return pos; };
	inline float GetNearPlane() const { return nearPlane; };
	inline float GetFarPlane() const { return farPlane; };
	inline vector<LightSource*> listLightSources() { return lightSources; };

	void SetPos(vec3 pos_);
	void SetRotation(float yaw_, float pitch_);

private:
	void UpdateCameraVectors();

	vec3 pos;
	mat4 perspective, ortho, view, projection;
	float fieldOfView;
	float yaw, pitch;
	float nearPlane, farPlane;
	vec3 forward, up, right, worldUp;

	vector<LightSource*> lightSources;
};

#endif