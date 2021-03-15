#include "LightSource.h"

LightSource::LightSource(vec3 pos_, float ambient_, float diffuse_, float specular_, vec3 colour_) : pos(0.0f, 0.0f, 0.0f), ambient(0.0f), diffuse(0.0f), specular(0.0f), colour(0.0f, 0.0f, 0.0f)
{
	pos = pos_;
	ambient = ambient_;
	diffuse = diffuse_;
	specular = specular_;
	colour = colour_;
}

LightSource::~LightSource() {}

void LightSource::SetPos(vec3 pos_)
{
	pos = pos_;
}

void LightSource::SetAmbient(float ambient_)
{
	ambient = ambient_;
}

void LightSource::SetDiffuse(float diffuse_)
{
	diffuse = diffuse_;
}

void LightSource::SetSpecular(float specular_)
{
	specular = specular_;
}

void LightSource::SetColour(vec3 colour_)
{
	colour = colour_;
}