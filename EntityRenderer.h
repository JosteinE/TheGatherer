#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shader.hpp>
#include "Vector2d.h"
class Entity;

class EntityRenderer
{
public:
	EntityRenderer();
	~EntityRenderer();

	void setLightPosition(sf::Shader * shader, Entity* inEntity);
	void drawEntity(sf::RenderTarget & target, sf::Shader * shader, Entity* inEntity);
};

