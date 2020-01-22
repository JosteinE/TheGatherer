#pragma once
#include <unordered_map>
#include <memory>
#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include "Vector2d.h"
struct SpriteComponent;
struct AnimationComponent;

class SpriteManager
{
private:
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> mTextures;
public:
	SpriteManager();
	~SpriteManager();

	void createSprite(SpriteComponent* spriteComp, const std::string* texturePath = nullptr);
	void centerSpriteOrigin(SpriteComponent* spriteComp, AnimationComponent* animComp = nullptr);
	void setPosition(SpriteComponent* spriteComp, Vector2d* pos);

	// Texture
	void addTexture(const std::string* path);
	void addTextureToSprite(const std::string* path, SpriteComponent* spriteComp);
	std::shared_ptr<sf::Texture> getTexture(const std::string* path);
	std::shared_ptr<sf::Texture> addAndGetTexture(const std::string* path);

private:
	bool checkTextureExistance(const std::string* path);
};

