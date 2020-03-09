#include "LightManager.h"
#include "EntityManager.h"
#include "LightComponent.h"
#include "Vector2d.h"


LightManager::LightManager()
{
}


LightManager::~LightManager()
{
}

void LightManager::createLight(EntityManager * entManager)
{
	entManager->createNewEntity(LIGHT_ENTITY, 0, true, false);
	entManager->getLastEntity()->addComponent(LIGHT_COMPONENT);
}

void LightManager::renderLight(LightComponent * inLight, Vector2d * lightPos)
{
}

void LightManager::updateEnvironmentLight(sf::Shader * inShader, int inCurrentHour, float deltaTime, bool continous)
{
	if (bEnvLightTransitioned)
	{
		if (currentHour == inCurrentHour)
			return;
		
		currentHour = inCurrentHour;

		if (!continous)
		{
			switch (currentHour)
			{
			case TIME_AFTERNOON:
				lastHour = TIME_NIGHT; break;
			case TIME_EVENING:
				lastHour = TIME_AFTERNOON; break;
			case TIME_NIGHT:
				lastHour = TIME_EVENING; break;
			default:
				return;
			}
		}
		else if (currentHour == 0)
			lastHour = 23; else lastHour = currentHour - 1;

		bEnvLightTransitioned = false;
	}

	int lastHoursFromMidnight = lastHour;
	float ambientLight;
	float currentLight[3];

	if (lastHour > 12)
		lastHoursFromMidnight = (12 - (lastHour - 12));

	if (dtLog == 0.f) // If the transition hasn't been initialized
	{
		for (int i = 0; i < 3; i++)
			lightDim[i] = (1 - desiredMidnightLightColour[i]) / 12.f;

		ambientLight = 1.f - lastHoursFromMidnight * ambientLightDim;
		for (unsigned int i = 0; i < 3; i++)
			currentLight[i] = 1.f - lastHoursFromMidnight * lightDim[i];
	}
	else
	{
		if (dtLog >= 1)
		{
			dtLog = 1;
			bEnvLightTransitioned = true;
		}

		int hoursFromMidnight = currentHour;
		if (currentHour > 12)
			hoursFromMidnight = (12 - (currentHour - 12));

		ambientLight = 1.f - (lastHoursFromMidnight + (hoursFromMidnight - lastHoursFromMidnight) * envLightTransitionSpeed * dtLog) * ambientLightDim;

		for (unsigned int i = 0; i < 3; i++)
			currentLight[i] = 1.f - (lastHoursFromMidnight + (hoursFromMidnight - lastHoursFromMidnight) * envLightTransitionSpeed * dtLog) * lightDim[i];
	}

	if (!bEnvLightTransitioned)
		dtLog += deltaTime;  else dtLog = 0;

	sf::Glsl::Vec4 ambientColour{ ambientLight, ambientLight, ambientLight, 1 };
	sf::Glsl::Vec4 lightColour{ currentLight[0], currentLight[1], currentLight[2], 1 };
	float lightRadius = 20;					// Belongs with the light source entity
	float shadeAlpha = ambientLight;		// Belongs with the light source entity

	inShader->setUniform("ambientColour", ambientColour);
	inShader->setUniform("lightColour", lightColour);
	inShader->setUniform("lightRadius", lightRadius);
	inShader->setUniform("shadeAlpha", shadeAlpha);
}
