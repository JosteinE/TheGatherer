#pragma once

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Vertex.hpp"

class TextureManager
{
private:
	sf::Vector2i defaultTileSize{ 16, 16 };

public:
	TextureManager();
	~TextureManager();

	void setVertexTileTexture(sf::Vertex* vertex, sf::Texture* texture, unsigned int tileIndex);
};

