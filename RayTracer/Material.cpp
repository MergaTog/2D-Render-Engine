#include "Material.h"

bool Lambertian::Scatter(const Ray_t& ray, const raycastHit_t& hit, glm::vec3& attenuation, Ray_t& scattered) const
{
	glm::vec3 target = hit.point + hit.normal + randomInUnitSphere();
	glm::vec3 direction = glm::normalize(target - hit.point);

	scattered = { hit.point, direction };
	attenuation = albedo->value(hit.uv, hit.point);
	return true;
}

bool Metal::Scatter(const Ray_t& ray, const raycastHit_t& hit, glm::vec3& attenuation, Ray_t& scattered) const
{
	glm::vec3 reflected = reflect(glm::normalize(ray.direction), hit.normal);

	scattered.origin = hit.point;
	scattered.direction = reflected + (randomInUnitSphere() * fuzz);
	attenuation = albedo->value(hit.uv, hit.point);

	return glm::dot(scattered.direction, hit.normal) > 0;
}

bool Dielectric::Scatter(const Ray_t& r, const raycastHit_t& hit, glm::vec3& attenuation, Ray_t& scattered) const
{
	attenuation = albedo->value(hit.uv, hit.point);

	glm::vec3 refracted;
	glm::vec3 normal;
	float cosine;
	float refractionRatio;

	if (glm::dot(r.direction, hit.normal) > 0)
	{
		normal = -hit.normal;
		refractionRatio = refractIndex;
		cosine = refractIndex * glm::dot(r.direction, hit.normal) / r.direction.length();

	}
	else
	{
		normal = hit.normal;
		refractionRatio = refractIndex;
		cosine = -glm::dot(r.direction, hit.normal) / r.direction.length();
	}

	float reflectProbability = 1.0f;
	if (refract(r.direction, normal, refractionRatio, refracted))
	{
		reflectProbability = schlick(cosine, refractIndex);
	}

	glm::vec3 reflected = reflect(glm::normalize(r.direction), hit.normal);
	scattered = (random01() < reflectProbability) ? Ray_t{ hit.point, reflected } : Ray_t{ hit.point, refracted };
	return true;
}