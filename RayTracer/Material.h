#pragma once
#include "Geometry.h"
#include "Sphere.h"
#include "Types.h"
#include "Sampler.h"
class Material
{
public:
	virtual bool Scatter(const Ray_t& ray, const raycastHit_t& hit, glm::vec3& attenuation, Ray_t& scattered)
		const = 0;
	virtual glm::vec3 Emitter(const glm::vec2& uv, const glm::vec3& point)
		{
			return glm::vec3{ 0,0,0};
		}
};

class Lambertian : public Material
{
public:
	Lambertian(const glm::vec3& albedo) : albedo{ std::make_shared<ColorSampler>(albedo) } {}
	Lambertian(std::shared_ptr<Sampler> albedo) : albedo{ albedo }{}
	bool Scatter(const Ray_t& ray, const raycastHit_t& hit, glm::vec3& attenuation, Ray_t& scattered)
		const override;
protected:
	std::shared_ptr<Sampler> albedo;
};

class Metal : public Material
{
public:
	Metal(const glm::vec3& albedo, float fuzz) : albedo{ std::make_shared<ColorSampler>(albedo) }, fuzz{ fuzz } {}
	Metal(std::shared_ptr<Sampler> albedo, float fuzz) : albedo{ albedo }, fuzz{ fuzz }{}
	bool Scatter(const Ray_t& ray, const raycastHit_t& hit, glm::vec3& attenuation, Ray_t& scattered)
		const override;

protected:
	std::shared_ptr<Sampler> albedo;
	float fuzz = 0;
};

class Dielectric : public Material
{
public:
	Dielectric(const glm::vec3& albedo, float refractIndex) : albedo{ std::make_shared<ColorSampler>(albedo) }, refractIndex{ refractIndex }{}
	Dielectric(std::shared_ptr<Sampler> albedo, float refractIndex) : albedo{ albedo }, refractIndex{ refractIndex } {}
	virtual bool Scatter(const Ray_t& r, const raycastHit_t& hit, glm::vec3& attenuation, Ray_t& scattered) const override;
	
protected:
	std::shared_ptr<Sampler> albedo;
	//glm::vec3 albedo{ 1,1,1 };
	float refractIndex{ 1 };
};

class Emissive : public Material
{
public:
	Emissive(const glm::vec3& color) : emission{ std::make_shared<ColorSampler>(color)} {}
	Emissive(std::shared_ptr<Sampler> emission) : emission{ emission } {}

	virtual bool Scatter(const Ray_t& ray, const raycastHit_t& hit, glm::vec3& attenuation, Ray_t& scattered) const override
	{
		return false;
	}

	virtual glm::vec3 Emitter(const glm::vec2& uv, const glm::vec3& point)
	{
		return emission->value(uv, point);
	}

protected:
	std::shared_ptr<Sampler> emission;
};