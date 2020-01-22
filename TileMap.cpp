#include "TileMap.h"

bool TileMap::load()
{
	// load the tileset texture
	if (!m_tileset.loadFromFile(mTileMapData.tileset))
		return false;

	// resize the vertex array to fit the level size
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(static_cast<int>(mTileMapData.tileSetSize.x) * static_cast<int>(mTileMapData.tileSetSize.y) * 4);

	const int tileWidth = static_cast<int>(mTileMapData.tileSize.x);
	const int tileHeight = static_cast<int>(mTileMapData.tileSize.y);
	const float centerWidth = (tileWidth * mTileMapData.tileSetSize.x) * -0.5f;
	const float centerHeight = (tileHeight * mTileMapData.tileSetSize.y) * -0.5f;

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

unsigned int TileMap::getTileIndex(Vector2d * pos)
{
	int tilesetStartX = (mTileMapData.tileSize.x * mTileMapData.tileSetSize.x) * -0.5f;
	int tilesetStartY = (mTileMapData.tileSize.y * mTileMapData.tileSetSize.y) * -0.5f;

	int posX = (static_cast<int>(pos->x) - tilesetStartX) / mTileMapData.tileSize.x;
	int posY = (static_cast<int>(pos->y) - tilesetStartY) / mTileMapData.tileSize.y;

	return posX + (mTileMapData.tileSetSize.x * posY);
}

void TileMap::setTileTexture(unsigned int tileIndex, unsigned int textureIndex)
{
	// get a pointer to the current tile's quad
	if (tileIndex * 4 < static_cast<int>(mTileMapData.tileSetSize.x) * static_cast<int>(mTileMapData.tileSetSize.y) * 4) // LAME IF
	{
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

std::vector<unsigned int> TileMap::getArea(unsigned int tileIndex, unsigned int xExtent, unsigned int yExtent, bool includeFirst)
{
	std::vector<unsigned int> areaTiles;

	// Progressively add indicies to our vector. Start from the tileIndex and check the horizontals first.
	// For each horizontal, scan for tiles above and below and add them until a limit is reached (no tile or max extent).

	areaTiles.push_back(tileIndex);

	for (int x = 0; x < xExtent * 2; x++)
	{
		if (x < xExtent)
		{
			// Does the plane to the right exist?
			if ((tileIndex + x + 1) % static_cast<int>(mTileMapData.tileSetSize.y) != 0)
				areaTiles.push_back(static_cast<unsigned int>(tileIndex + x + 1));
		}
		else
		{
			// Does the plane to the left exist?
			if ((tileIndex - (x - xExtent) + static_cast<int>(mTileMapData.tileSetSize.y)) % static_cast<int>(mTileMapData.tileSetSize.y) != 0)
				areaTiles.push_back(static_cast<unsigned int>(tileIndex - (x - xExtent) - 1));
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
				if (areaTiles[i] - (y * static_cast<int>(mTileMapData.tileSetSize.x) > static_cast<int>(mTileMapData.tileSetSize.x)))
					areaTiles.push_back(static_cast<unsigned int>(areaTiles[i] - (y * static_cast<int>(mTileMapData.tileSetSize.x))));
			}
			else
			{
				// Does the plane below exist?
				if (areaTiles[i] + ((y - yExtent - 1) * static_cast<int>(mTileMapData.tileSetSize.x) < (static_cast<int>(mTileMapData.tileSetSize.x) - 1) * static_cast<int>(mTileMapData.tileSetSize.y)))
					areaTiles.push_back(static_cast<unsigned int>(areaTiles[i] + ((y - yExtent - 1) * static_cast<int>(mTileMapData.tileSetSize.x)) + static_cast<int>(mTileMapData.tileSetSize.y)));
			}
		}
	}

	if(!includeFirst)
		areaTiles.erase(areaTiles.begin());

	return areaTiles;
}
