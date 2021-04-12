#include "Camera.h"

#include "../Core/CoreEngine.h"

Camera::Camera() : pos(vec3()), fieldOfView(0.0f), forward(vec3()), up(vec3()), right(vec3()), worldUp(vec3()), nearPlane(0.0f), farPlane(0.0f), yaw(0.0f), pitch(0.0f), perspective(mat4()), ortho(mat4()), view(mat4())
{
	fieldOfView = 45.0f;
	forward = vec3(0.0f, 0.0f, -1.0f);
	up = vec3(0.0f, 1.0f, 0.0f);
	worldUp = up;
	nearPlane = 2.0f;
	farPlane = 50.0f;
	yaw = -90.0f;
	pitch = 0.0f;

	perspective = glm::perspective(fieldOfView, CoreEngine::GetInstance()->GetScreenWidth() / CoreEngine::GetInstance()->GetScreenHeight(), nearPlane, farPlane);
	ortho = glm::ortho(0.0f, CoreEngine::GetInstance()->GetScreenWidth(), 0.0f, CoreEngine::GetInstance()->GetScreenHeight(), -1.0f, 1.0f);

	UpdateCameraVectors();
}

Camera::~Camera()
{
	if (lightSources.size() > 0)
	{
		for (auto t : lightSources)
		{
			delete t;
			t = nullptr;
		}
		lightSources.clear();
	}
}

void Camera::SetPos(vec3 pos_)
{
	pos = pos_;
	UpdateCameraVectors();
}

void Camera::SetRotation(float yaw_, float pitch_)
{
	yaw = yaw_;
	pitch = pitch_;
	UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
	forward.x = cos(radians(yaw)) * cos(radians(pitch));
	forward.y = sin(radians(pitch));
	forward.z = sin(radians(yaw)) * cos(radians(pitch));

	forward = normalize(forward);
	right = normalize(cross(forward, worldUp));
	up = normalize(cross(right, forward));
	view = lookAt(pos, pos + forward, up);
}

void Camera::addLightSource(vec3 pos_, float ambient_, float diffuse_, float specular_, vec3 colour_)
{
	LightSource* light = new LightSource(pos_, ambient_, diffuse_, specular_, colour_);
	lightSources.push_back(light);
}

void Camera::ProcessMouseMovement(vec2 offset_)
{
	offset_ *= 0.05f;

	yaw += offset_.x;
	pitch -= offset_.y;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	if (yaw < 0.0f)
	{
		yaw += 360.0f;
	}
	if (yaw > 360.0f)
	{
		yaw -= 360.0f;
	}
	UpdateCameraVectors();
}

void Camera::ProcessMouseZoom(int y_)
{
	if (y_ < 0 || y_ > 0)
	{
		pos += static_cast<float>(y_) * (forward * 2.0f);
	}

	UpdateCameraVectors();
}