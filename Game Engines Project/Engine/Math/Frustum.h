#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <glm/glm.hpp>

using namespace glm;

struct Plane
{
	float x, y, z, w;
};

struct Frustum
{
	
	Plane planes[6];

	void MakeFrustum(mat4 projMat_);
};

#endif;