#pragma once

class EntityManager;
class Vector2d;
struct LightComponent;

class LightManager
{
public:
	LightManager();
	~LightManager();

	void createLight(EntityManager* EntManager);
	void renderLight(LightComponent* inLight, Vector2d lightPos);
};

