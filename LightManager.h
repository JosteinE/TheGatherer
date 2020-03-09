#pragma once

#include <SFML/Graphics/Shader.hpp>

class EntityManager;
class Vector2d;
struct LightComponent;

// https://youtu.be/iyUs9DdSPRA?t=389

enum DAYTIME
{
	TIME_AFTERNOON = 0,
	TIME_EVENING = 8,
	TIME_NIGHT = 12
};

// 0 = brightest, 12 = darkest
enum SUNLIGHT
{
	SUNLIGHT_AFTERNOON = 0,
	SUNLIGHT_EVENING = 5,
	SUNLIGHT_NIGHT = 12
};

class LightManager
{
public:
	LightManager();
	~LightManager();

	void createLight(EntityManager* entManager);
	void renderLight(LightComponent* inLight, Vector2d* lightPos);
	void updateEnvironmentLight(sf::Shader * inShader, int currentHour, bool continous = true); // continues means that the light changes every hour
};

