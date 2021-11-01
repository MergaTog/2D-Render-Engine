#pragma once
#include <iostream>
#include "Types.h"
#include "Ray.h"




struct raycastHit_t
{
    float t{ 0 };
    glm::vec3 point;
    glm::vec3 normal;
    class Material* material;
};

class Geometry
{
public:
    std::shared_ptr<Material> material;
    Geometry() = default;
    virtual ~Geometry() = default;
    Geometry(std::shared_ptr<Material> material): material(material) {}

    virtual bool Hit(const Ray_t& r, float tMin, float tMax, raycastHit_t& hit) = 0;
};
