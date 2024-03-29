#pragma once

#include <iostream>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "Vector2d.h"
#include "TileMapComponent.h"

/* Inspired by this guide on VertexArrays
https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
*/

class TileMap : public sf::Drawable, public sf::Transformable
{
private:
	bool bMapCentered{ false };
public:
	TileMapComponent mTileMapData;

	Vector2d mapCenter;
	bool load(bool centerMap);

	sf::Vertex* getTile(unsigned int index);
	int getTileIndex(Vector2d* pos);
	unsigned int getTileTextureIndex(int tileIndex);
	std::vector<unsigned int> getArea(int tileIndex, unsigned int xExtent = 1, unsigned int yExtent = 1, bool includeFirst = true);

	void setShader(sf::Shader * inShader);
	bool setTexture(std::string * texturePath);

	void setTileTexture(unsigned int tileIndex, unsigned int textureIndex);
	void setTileColour(unsigned int tileIndex, unsigned int r = 255, unsigned int g = 255, unsigned int b = 255, unsigned int a = 255);
	std::vector<unsigned int> getFrustum(int tileIndex, int width, int height);
	sf::VertexArray* getVertices();
	sf::Texture* getTexture();

	void drawFrustum(sf::RenderTarget& target, sf::Shader * shader, double camZoom, Vector2d * position, int width, int height);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	sf::RenderStates m_renderState;
};

