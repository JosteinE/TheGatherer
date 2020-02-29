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
