#include "TextureManager.h"
#include <iostream>


TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

void TextureManager::setVertexTileTexture(sf::Vertex * vertex, sf::Texture * texture, unsigned int tileIndex)
{
	int numColumns = static_cast<int>(texture->getSize().x / defaultTileSize.x);
	int numRows = static_cast<int>(texture->getSize().y / defaultTileSize.y);

	if (numRows * numColumns < tileIndex)
	{
		std::cout << "The specified tile does not exist in the given texture!" << std::endl;
	}

	int tu = tileIndex % numColumns;
	int tv = static_cast<int>(tileIndex / (numColumns + 1));

	// define its 4 texture coordinates
	vertex[0].texCoords = sf::Vector2f(tu * static_cast<int>(defaultTileSize.x), tv * static_cast<int>(defaultTileSize.y));
	vertex[1].texCoords = sf::Vector2f((tu + 1) * static_cast<int>(defaultTileSize.x), tv * static_cast<int>(defaultTileSize.y));
	vertex[2].texCoords = sf::Vector2f((tu + 1) * static_cast<int>(defaultTileSize.x), (tv + 1) * static_cast<int>(defaultTileSize.y));
	vertex[3].texCoords = sf::Vector2f(tu * static_cast<int>(defaultTileSize.x), (tv + 1) * static_cast<int>(defaultTileSize.y));
}
