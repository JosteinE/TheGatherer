#pragma once
#include "Vector2d.h"
#include <SFML/Graphics/Texture.hpp>
#include <vector>

class Entity;
class EntityManager;

/* VertexArray
https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
*/

class LandscapeGenerator
{
private:
	Vector2d mPosition;
	Vector2d* mTileSize;
	Vector2d* mTileSetSize;
	Vector2d* mTileSpacing;
	std::string mTexturePath;
	std::shared_ptr<sf::Texture> mTexture = nullptr;
	bool bTextureLoaded{ false };
public:
	LandscapeGenerator(Vector2d inPosition, Vector2d* inTileSize = nullptr, Vector2d* inTileSetSize = nullptr, Vector2d* inTileSpacing = nullptr);
	~LandscapeGenerator();

	void setPosition(Vector2d inPosition);
	void setTileSize(Vector2d* inTileSize);
	void setTileSetSize(Vector2d* inTileSetSize);
	void setTileSpacing(Vector2d* inTileSpacing);
	void setTexture(const std::string* filePath);

	void construct(EntityManager* entM, std::vector<int>* components = nullptr);
};

