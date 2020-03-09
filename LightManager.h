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
private:
	float envLightTransitionSpeed = 1.f;
	int lastHour;
	int currentHour = -1;


	// Environmental Light
	float dtLog = 0.f;
	float ambientLightDim = (100.f / 12.f) / 100.f;
	float lightDim[3];											// Belongs with the light source entity
	float desiredMidnightLightColour[3]{ 0.252, 0.188, 0.141 }; // Belongs with the light source entity

public:
	LightManager();
	~LightManager();

	bool bEnvLightTransitioned{ true };

	void createLight(EntityManager* entManager);
	void renderLight(LightComponent* inLight, Vector2d* lightPos);
	void updateEnvironmentLight(sf::Shader * inShader, int inCurrentHour, float deltaTime = 0.f, bool continous = true); // continues means that the light changes every hour
};

