#pragma once
#include "Geometry.h"
#include "Sphere.h"
#include "Types.h"
class Material
{
public:
	virtual bool Scatter(const Ray_t& ray, const raycastHit_t& hit, glm::vec3& attenuation, Ray_t& scattered)
		const = 0;
};

class Lambertian : public Material
{
public:
	Lambertian(const glm::vec3& albedo) : albedo{ albedo } {}
	bool Scatter(const Ray_t& ray, const raycastHit_t& hit, glm::vec3& attenuation, Ray_t& scattered)
		const override;
protected:
	glm::vec3 albedo{0,0,0};
};

class Metal : public Material
{
public:
	Metal(const glm::vec3& albedo, float fuzz) : albedo{ albedo }, fuzz{ fuzz } {}
	bool Scatter(const Ray_t& ray, const raycastHit_t& hit, glm::vec3& attenuation, Ray_t& scattered)
		const override;

protected:
	glm::vec3 albedo{ 0,0,0 };
	float fuzz = 0;
};