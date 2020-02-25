#include "TileMap.h"
#include <iostream>

bool TileMap::load(bool centerMap)
{
	// load the tileset texture
	if (!m_tileset.loadFromFile(mTileMapData.tileset))
		return false;

	// resize the vertex array to fit the level size
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(static_cast<int>(mTileMapData.tileSetSize.x) * static_cast<int>(mTileMapData.tileSetSize.y) * 4);

	const int tileWidth = static_cast<int>(mTileMapData.tileSize.x);
	const int tileHeight = static_cast<int>(mTileMapData.tileSize.y);
	float centerWidth;
	float centerHeight;

	if (centerMap)
	{
		centerWidth = (tileWidth * mTileMapData.tileSetSize.x) * -0.5f;
		centerHeight = (tileHeight * mTileMapData.tileSetSize.y) * -0.5f;
		mapCenter = Vector2d{ 0, 0 };
		bMapCentered = true;
	}
	else
	{
		centerWidth = 0;
		centerHeight = 0;
		mapCenter = Vector2d{ (tileWidth * mTileMapData.tileSetSize.x) * 0.5f , (tileHeight * mTileMapData.tileSetSize.y) * 0.5f };
	}

	// populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < static_cast<int>(mTileMapData.tileSetSize.x); ++i)
		for (unsigned int j = 0; j < static_cast<int>(mTileMapData.tileSetSize.y); ++j)
		{
			// get the current tile number
			int tileNumber = mTileMapData.map[i + j * static_cast<int>(mTileMapData.tileSetSize.x)];

			// find its position in the tileset texture
			int tu = tileNumber % (m_tileset.getSize().x / tileWidth);
			int tv = tileNumber / (m_tileset.getSize().x / tileWidth);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * static_cast<int>(mTileMapData.tileSetSize.x)) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(i * tileWidth + centerWidth, j * tileHeight + centerHeight);
			quad[1].position = sf::Vector2f((i + 1) * tileWidth + centerWidth, j * tileHeight + centerHeight);
			quad[2].position = sf::Vector2f((i + 1) * tileWidth + centerWidth, (j + 1) * tileHeight + centerHeight);
			quad[3].position = sf::Vector2f(i * tileWidth + centerWidth, (j + 1) * tileHeight + centerHeight);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileWidth, tv * tileHeight);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileWidth, tv * tileHeight);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileWidth, (tv + 1) * tileHeight);
			quad[3].texCoords = sf::Vector2f(tu * tileWidth, (tv + 1) * tileHeight);
		}

	return true;
}

sf::Vertex * TileMap::getTile(unsigned int index)
{
	return &m_vertices[index * 4];
}

int TileMap::getTileIndex(Vector2d * pos)
{
	int tilesetStartX;
	int tilesetStartY;

	if (bMapCentered)
	{
		tilesetStartX = (mTileMapData.tileSize.x * mTileMapData.tileSetSize.x) * -0.5f;
		tilesetStartY = (mTileMapData.tileSize.y * mTileMapData.tileSetSize.y) * -0.5f;
	}
	else
	{
		tilesetStartX = 0;
		tilesetStartY = 0;
	}

	if ((static_cast<int>(pos->x) - tilesetStartX) < 0 || (static_cast<int>(pos->y) - tilesetStartY) < 0)
		return -1;

	int posX = (static_cast<int>(pos->x) - tilesetStartX) / mTileMapData.tileSize.x;
	int posY = (static_cast<int>(pos->y) - tilesetStartY) / mTileMapData.tileSize.y;

	if (posX >= mTileMapData.tileSetSize.x || posY >= mTileMapData.tileSetSize.y)
	{
		std::cout << "There is no tile on the given location!" << std::endl;
		return -1;
	}
	else
	{
		//std::cout << "TileIndex: " << posX + (mTileMapData.tileSetSize.x * posY) << std::endl;
		return posX + (mTileMapData.tileSetSize.x * posY);
	}
}

unsigned int TileMap::getTileTextureIndex(int tileIndex)
{
	return getTile(tileIndex)->texCoords.x / static_cast<int>(mTileMapData.tileSize.x);
}

void TileMap::setTileTexture(unsigned int tileIndex, unsigned int textureIndex)
{
	// get a pointer to the current tile's quad
		sf::Vertex* quad = &m_vertices[tileIndex * 4];

		// find its position in the tileset texture
		int tu = textureIndex % (m_tileset.getSize().x / static_cast<int>(mTileMapData.tileSize.x));
		int tv = textureIndex / (m_tileset.getSize().x / static_cast<int>(mTileMapData.tileSize.x));

		// define its 4 texture coordinates
		quad[0].texCoords = sf::Vector2f(tu * static_cast<int>(mTileMapData.tileSize.x), tv * static_cast<int>(mTileMapData.tileSize.y));
		quad[1].texCoords = sf::Vector2f((tu + 1) * static_cast<int>(mTileMapData.tileSize.x), tv * static_cast<int>(mTileMapData.tileSize.y));
		quad[2].texCoords = sf::Vector2f((tu + 1) * static_cast<int>(mTileMapData.tileSize.x), (tv + 1) * static_cast<int>(mTileMapData.tileSize.y));
		quad[3].texCoords = sf::Vector2f(tu * static_cast<int>(mTileMapData.tileSize.x), (tv + 1) * static_cast<int>(mTileMapData.tileSize.y));
}

void TileMap::setTileColour(unsigned int tileIndex, unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	sf::Vertex* quad = getTile(tileIndex);
	for (int i = 0; i < 4; i++)
	{
		quad[i].color.r = r;
		quad[i].color.g = g;
		quad[i].color.b = b;
		quad[i].color.a = a;
	}
}

std::vector<unsigned int> TileMap::getFrustum(int tileIndex, int width, int height)
{
		std::vector<unsigned int> indices;
		for (int x = height; x >= -height; x--)
		{
			if (tileIndex - (x * static_cast<int>(mTileMapData.tileSetSize.x)) - width >= 0 &&
				tileIndex - (x * static_cast<int>(mTileMapData.tileSetSize.x)) - width <
				static_cast<int>(mTileMapData.tileSetSize.x) * static_cast<int>(mTileMapData.tileSetSize.y))
			{
				indices.push_back(tileIndex - (x * mTileMapData.tileSetSize.x) - width);
			}
		}
		return indices;
}

sf::VertexArray * TileMap::getVertices()
{
	return &m_vertices;
}

sf::Texture * TileMap::getTexture()
{
	return &m_tileset;
}

void TileMap::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
			// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &m_tileset;

		// draw the vertex array
		target.draw(m_vertices, states);
}

std::vector<unsigned int> TileMap::getArea(int tileIndex, unsigned int xExtent, unsigned int yExtent, bool includeFirst)
{
	std::vector<unsigned int> areaTiles;

	// Progressively add indicies to our vector. Start from the tileIndex and check the horizontals first.
	// For each horizontal, scan for tiles above and below and add them until a limit is reached (no tile or max extent).

	if (tileIndex < static_cast<int>(mTileMapData.tileSetSize.x) * static_cast<int>(mTileMapData.tileSetSize.y) && tileIndex >= 0)
	{
		areaTiles.push_back(tileIndex);

		for (int x = 1; x <= xExtent * 2; x++)
		{
			if (x <= xExtent)
			{
				// Does the plane to the right exist?
				if ((tileIndex + x) % static_cast<int>(mTileMapData.tileSetSize.x) != 0)
					areaTiles.push_back(static_cast<unsigned int>(tileIndex + x));
				else
					x = xExtent; // Prevents the program for scanning for indices further to the right when one isn't found.
			}
			else
			{
				// Does the plane to the left exist?
				if ((tileIndex - (x - xExtent) + static_cast<int>(mTileMapData.tileSetSize.x) + 1) % static_cast<int>(mTileMapData.tileSetSize.x) != 0)
					areaTiles.push_back(static_cast<unsigned int>(tileIndex - (x - xExtent)));
				else
					break;
			}
		}

		int numX = areaTiles.size();
		for (int i = 0; i < numX; i++)
		{
			for (int y = 1; y <= yExtent * 2; y++)
			{
				if (y <= yExtent)
				{
					// Does the plane above exist?
					if (static_cast<int>(areaTiles[i] - (y * static_cast<int>(mTileMapData.tileSetSize.x))) >= 0)
						areaTiles.push_back(static_cast<unsigned int>(areaTiles[i] - (y * static_cast<int>(mTileMapData.tileSetSize.x))));
					else
						y = yExtent; // Prevents the program for scanning for indices further to the right when one isn't found.
				}
				else
				{
					// Does the plane below exist?
					if (static_cast<int>(areaTiles[i] + ((y - yExtent) * static_cast<int>(mTileMapData.tileSetSize.x))) < static_cast<int>(mTileMapData.tileSetSize.x) * static_cast<int>(mTileMapData.tileSetSize.y))
						areaTiles.push_back(static_cast<unsigned int>(areaTiles[i] + ((y - yExtent) * static_cast<int>(mTileMapData.tileSetSize.x))));
					else
						break;
				}
			}
		}

		if (!includeFirst)
			areaTiles.erase(areaTiles.begin());
	}
	
	return areaTiles;
}
