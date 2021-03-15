#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <vector>
#include <glm/glm.hpp>

using namespace glm;

class LightSource
{
public:
	LightSource(vec3 pos_, float ambient_, float diffuse_, float specular_, vec3 colour_);
	~LightSource();

	inline vec3 GetPos() { return pos; };
	inline float GetAmbient() { return ambient; };
	inline float GetDiffuse() { return diffuse; };
	inline float GetSpecular() { return specular; };
	inline vec3 GetColour() { return colour; };

	void SetPos(vec3 pos_);
	void SetAmbient(float ambient_);
	void SetDiffuse(float diffuse_);
	void SetSpecular(float specular_);
	void SetColour(vec3 colour_);

private:
	vec3 pos;
	float ambient;
	float diffuse;
	float specular;
	vec3 colour;
};

#endif