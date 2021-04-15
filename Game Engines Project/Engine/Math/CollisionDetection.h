#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "../Camera/Camera.h"

struct Ray;
struct BoundingBox;

class CollisionDetection
{
public:
	CollisionDetection(const CollisionDetection&) = delete;
	CollisionDetection(CollisionDetection&&) = delete;
	CollisionDetection& operator=(const CollisionDetection&) = delete;
	CollisionDetection& operator=(CollisionDetection&&) = delete;

	CollisionDetection() = delete;
	~CollisionDetection();

	static Ray MousePosToWorldRay(vec2 mouseCoords_, float screenWisth_, float screenHeight_, Camera* camera_);
	static bool RayObbIntersection(Ray* ray_, BoundingBox* box_);
		
};

#endif;