#include "Frustum.h"

void Frustum::MakeFrustum(mat4 projMat_)
{
	// Right Plane
	planes[0].x = projMat_[0][3] - projMat_[0][0];
	planes[0].y = projMat_[1][3] - projMat_[1][0];
	planes[0].z = projMat_[2][3] - projMat_[2][0];
	planes[0].w = projMat_[3][3] - projMat_[3][0];
	//glm::normalize(planes[0]);

	// Left Plane
	planes[1].x = projMat_[0][3] + projMat_[0][0];
	planes[1].y = projMat_[1][3] + projMat_[1][0];
	planes[1].z = projMat_[2][3] + projMat_[2][0];
	planes[1].w = projMat_[3][3] + projMat_[3][0];
	//glm::normalize(planes[1]);

	// Top Plane
	planes[2].x = projMat_[0][3] - projMat_[0][1];
	planes[2].y = projMat_[1][3] - projMat_[1][1];
	planes[2].z = projMat_[2][3] - projMat_[2][1];
	planes[2].w = projMat_[3][3] - projMat_[3][1];
	//glm::normalize(planes[2]);

	// Bottom Plane
	planes[3].x = projMat_[0][3] + projMat_[0][1];
	planes[3].y = projMat_[1][3] + projMat_[1][1];
	planes[3].z = projMat_[2][3] + projMat_[2][1];
	planes[3].w = projMat_[3][3] + projMat_[3][1];
	//glm::normalize(planes[3]);

	// Near Plane
	planes[4].x = projMat_[0][3] - projMat_[0][2];
	planes[4].y = projMat_[1][3] - projMat_[1][2];
	planes[4].z = projMat_[2][3] - projMat_[2][2];
	planes[4].w = projMat_[3][3] - projMat_[3][2];
	//glm::normalize(planes[4]);

	// Far Plane
	planes[5].x = projMat_[0][3] + projMat_[0][2];
	planes[5].y = projMat_[1][3] + projMat_[1][2];
	planes[5].z = projMat_[2][3] + projMat_[2][2];
	planes[5].w = projMat_[3][3] + projMat_[3][2];
	//glm::normalize(planes[5]);
}
