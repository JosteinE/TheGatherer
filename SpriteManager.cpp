#include "SpriteManager.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"


SpriteManager::SpriteManager()
{
}


SpriteManager::~SpriteManager()
{
	mTextures.clear();
}

void SpriteManager::createSprite(SpriteComponent * spriteComp, const std::string* texturePath)
{
	if(texturePath == nullptr)
		spriteComp->mSprite = new sf::Sprite();
	else
	{
		if(checkTextureExistance(texturePath))
			spriteComp->mSprite = new sf::Sprite(*mTextures[*texturePath].get());
		else
			spriteComp->mSprite = new sf::Sprite(*addAndGetTexture(texturePath).get());
	}
}

void SpriteManager::centerSpriteOrigin(SpriteComponent * spriteComp, AnimationComponent * animComp)
{
	// Center the origin by multiplying the texture size by half, then divide that number by the number of frames
	if (animComp == nullptr)
		spriteComp->mSprite->setOrigin(sf::Vector2f(spriteComp->mSprite->getTexture()->getSize().x * 0.5f,
													spriteComp->mSprite->getTexture()->getSize().y * 0.5f));
	else // REMEMBER: Build sprite before using this!
		spriteComp->mSprite->setOrigin(sf::Vector2f(spriteComp->mSprite->getTexture()->getSize().x * 0.5f * (animComp->frameSize.x / spriteComp->mSprite->getTexture()->getSize().x),
													spriteComp->mSprite->getTexture()->getSize().y * 0.5f * (animComp->frameSize.y / spriteComp->mSprite->getTexture()->getSize().y)));
}

void SpriteManager::setPosition(SpriteComponent * spriteComp, Vector2d pos)
{
	spriteComp->mSprite->setPosition(pos.toSf());
}

void SpriteManager::addTexture(const std::string * path)
{
	std::shared_ptr<sf::Texture> newTexture = std::make_shared<sf::Texture>();
	if (newTexture->loadFromFile(*path))
		mTextures[*path] = newTexture;
	else
		std::cout << "Failed to load texture from this path: " << path << std::endl;
}

void SpriteManager::addTextureToSprite(const std::string * path, SpriteComponent * spriteComp)
{
	if (checkTextureExistance(path))
		spriteComp->mSprite->setTexture(*mTextures[*path].get());
	else
		spriteComp->mSprite->setTexture(*addAndGetTexture(path).get());

	spriteComp->mTexturePath = *path;
}

std::shared_ptr<sf::Texture> SpriteManager::getTexture(const std::string * path)
{
	if (checkTextureExistance(path))
		return mTextures[*path];
	else
		std::cout << "Could not find a texture from the following path: " << path << std::endl;
}

std::shared_ptr<sf::Texture> SpriteManager::addAndGetTexture(const std::string * path)
{
	addTexture(path);
	return mTextures[*path];
}

bool SpriteManager::checkTextureExistance(const std::string * path)
{
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>>::const_iterator it = mTextures.find(*path);
	if (it == mTextures.end())
		return false;
	else
		return true;
}
