#pragma once
#include "Types.h"

struct Ray_t
{
	glm::vec3 origin;
	glm::vec3 direction;

	Ray_t() = default;
	Ray_t(const glm::vec3 origin, const glm::vec3 direction) : origin{origin}, direction{direction}{}
	glm::vec3 pointAt(float t) const { return origin + (direction * t); }
};