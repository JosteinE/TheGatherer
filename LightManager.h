#pragma once

#include <SFML/Graphics/Shader.hpp>

class EntityManager;
class Vector2d;
struct LightComponent;

// https://youtu.be/iyUs9DdSPRA?t=389

class LightManager
{
public:
	LightManager();
	~LightManager();

	void createLight(EntityManager* entManager);
	void renderLight(LightComponent* inLight, Vector2d* lightPos);
};

