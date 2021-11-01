#include "Sphere.h"

bool Sphere::Hit(const Ray_t& r, float tMin, float tMax, raycastHit_t& hit)
{
    glm::vec3 oc = r.origin - center;
    float a = glm::dot(r.direction, r.direction);
    float b = 2 * glm::dot(r.direction, oc);
    float c = glm::dot(oc, oc) - (radius * radius);



    // c = distance from ray origin to sphere > radius
    // b = ray direction is facing away from sphere
    if (c > 0 && b > 0) return false;


    // b^2 - 4ac
    float discriminant = (b * b) - (4 * a * c);

    // discriminant == 0 - one intersection, discriminant > 0 - two intersections
    if (discriminant >= 0)
    {
        float t = (-b - sqrt(discriminant)) / (2 * a);
        if (t > tMin && t < tMax)
        {
            hit.t = t;
            hit.point = r.pointAt(hit.t);
            hit.normal = (hit.point - center) / radius;
            hit.material = material.get();
            return true;
        }


        t = (-b + sqrt(discriminant)) / (2 * a);
        if (t > tMin && t < tMax)
        {
            hit.t = t;
            hit.point = r.pointAt(hit.t);
            hit.normal = (hit.point - center) / radius;
            return true;
        }
    }
    return false;
}
