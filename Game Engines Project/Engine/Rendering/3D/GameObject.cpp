#include "GameObject.h"

GameObject::GameObject(Model* model_) : model(nullptr), pos(vec3()), angle(0.0f), rotation(vec3(0.0f, 1.0f, 0.0f)), scale(vec3(1.0f)), modelInstance(0)
{
	model = model_;
	if (model)
	{
		modelInstance = model->CreateInstance(pos, angle, rotation, scale);
	}
}

GameObject::GameObject(Model* model_, vec3 pos_) : model(nullptr), pos(vec3()), angle(0.0f), rotation(vec3(0.0f, 1.0f, 0.0f)), scale(vec3(1.0f)), modelInstance(0)
{
	model = model_;
	pos = pos_;
	if (model)
	{
		modelInstance = model->CreateInstance(pos, angle, rotation, scale);
	}
}

GameObject::~GameObject()
{
	model = nullptr;
}

void GameObject::Update(const float deltaTime_)
{
	SetAngle(angle + 0.005f);
}

void GameObject::Render(Camera* camera_)
{
	if (model)
	{
		model->Render(camera_);
	}
}

void GameObject::SetPos(vec3 pos_)
{
	pos = pos_;
	if (model)
	{
		model->UpdateInstance(modelInstance, pos, angle, rotation, scale);
	}
}

void GameObject::SetAngle(float angle_)
{
	angle = angle_;
	if (model)
	{
		model->UpdateInstance(modelInstance, pos, angle, rotation, scale);
	}
}

void GameObject::SetRotation(vec3 rotation_)
{
	rotation = rotation_;
	if (model)
	{
		model->UpdateInstance(modelInstance, pos, angle, rotation, scale);
	}
}

void GameObject::SetScale(vec3 scale_)
{
	scale = scale_;
	if (model)
	{
		model->UpdateInstance(modelInstance, pos, angle, rotation, scale);
	}
}

void GameObject::SetTag(string tag_)
{
	tag = tag_;
}