#pragma once
#include "Types.h"
#include "ColorBuffer.h"
#include "Camera.h"
#include <string>

class Scene;

class Tracer
{
public:
	void Trace(class Buffer* buffer, Scene* scene, Camera* camera, const std::string& message);

public:
	int samples = 1;
	int depth = 50;
};