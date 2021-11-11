#pragma once
#include "Types.h"

class Material;

struct raycastHit_t 
{
	float t{ 0 };     
	glm::vec3 point;     
	glm::vec3 normal;
	glm::vec2 uv;      
	class Material* material; 
};

struct Ray_t
{
	glm::vec3 origin;
	glm::vec3 direction;

	Ray_t() = default;
	Ray_t(const glm::vec3 origin, const glm::vec3 direction) : origin{origin}, direction{direction}{}

	glm::vec3 pointAt(float t) const { return origin + (direction * t); }
};

static glm::vec2 GetUV(const glm::vec3& point);

inline glm::vec2 GetPlanarUV(const glm::vec3& point)
{
	glm::vec2 uv{point.x, point.z};

	float i;
	uv[0] = modf(uv[0], &i);
	uv[1] = modf(uv[1], &i);

	uv[0] = (uv[0] < 0) ? 1 + uv[0] : uv[0];
	uv[1] = (uv[1] < 0) ? 1 + uv[1] : uv[1];

	return uv;
}

inline glm::vec2 GetSphericalUV(const glm::vec3 point)
{
	// p: a given point on the sphere of radius one, centered at the origin.
	// u: returned value [0,1] of angle around the Y axis from X=-1.
	// v: returned value [0,1] of angle from Y=-1 to Y=+1.
	//     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
	//     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
	//     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

	float theta = acos(-point.y);

	float phi = atan2(-point.z, point.x) + glm::pi<float>();

	glm::vec2 uv;

	uv[0] = phi / (2 * glm::pi<float>());
	uv[1] = theta / glm::pi<float>();

	return uv;
}

