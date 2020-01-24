#pragma once

#include <iostream>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "TileMapComponent.h"

/* Inspired by this guide on VertexArrays
https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
*/

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMapComponent mTileMapData;

	bool load();

	sf::Vertex* getTile(unsigned int index);
	int getTileIndex(Vector2d* pos);
	std::vector<unsigned int> getArea(int tileIndex, unsigned int xExtent = 1, unsigned int yExtent = 1, bool includeFirst = true);

	void setTileTexture(unsigned int tileIndex, unsigned int textureIndex);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
};

