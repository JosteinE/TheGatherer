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

void LightManager::updateEnvironmentLight(sf::Shader * inShader, int currentHour, bool continous)
{
	std::cout << "Current hour: " << currentHour << std::endl;

	if (!continous)
	{
		if (currentHour < TIME_EVENING)
			currentHour = SUNLIGHT_AFTERNOON;
		else if (currentHour < TIME_NIGHT)
			currentHour = SUNLIGHT_EVENING;
		else
			currentHour = SUNLIGHT_NIGHT;
	}

	float currentAmbientLight;
	float ambientLightDim = (100.f / 12.f) / 100.f;

	float currentLight[3];										// Belongs with the light source entity
	float desiredMidnightLightColour[3]{ 0.252, 0.188, 0.141 }; // Belongs with the light source entity

	if (currentHour <= 12)
	{
		currentAmbientLight = 1.f - currentHour * ambientLightDim;

		for (int i = 0; i < 3; i++)
			currentLight[i] = 1 - currentHour * ((1 - desiredMidnightLightColour[i]) / 12);
	}
	else
	{
		currentAmbientLight = 1 - (12 - (currentHour - 12)) * ambientLightDim;

		for (int i = 0; i < 3; i++)
			currentLight[i] = 1 - (12 - (currentHour - 12)) * ((1 - desiredMidnightLightColour[i]) / 12);
	}

	sf::Glsl::Vec4 ambientColour{ currentAmbientLight, currentAmbientLight, currentAmbientLight, 1 };
	sf::Glsl::Vec4 lightColour{ currentLight[0], currentLight[1], currentLight[2], 1 };
	float lightRadius = 20;					// Belongs with the light source entity
	float shadeAlpha = currentAmbientLight; // Belongs with the light source entity

	inShader->setUniform("ambientColour", ambientColour);
	inShader->setUniform("lightColour", lightColour);
	inShader->setUniform("lightRadius", lightRadius);
	inShader->setUniform("shadeAlpha", shadeAlpha);
}
