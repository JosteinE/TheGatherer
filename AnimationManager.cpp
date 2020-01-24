#include "AnimationManager.h"
#include "AnimationComponent.h"
#include "SpriteComponent.h"
#include "InputComponent.h"


AnimationManager::AnimationManager()
{
}


AnimationManager::~AnimationManager()
{
}

void AnimationManager::buildAnim(AnimationComponent * inAnimComp, SpriteComponent* inSprite, Vector2d frameSize)
{
	inAnimComp->frameSize = frameSize;
	inAnimComp->numFrames = inSprite->mSprite->getTexture()->getSize().x / frameSize.x;
	inAnimComp->numLayers = inSprite->mSprite->getTexture()->getSize().y / frameSize.y;

	setLayerAndFrame(inAnimComp, inSprite, 0, 0);
}

void AnimationManager::setAnimLayer(AnimationComponent * inAnimComp, unsigned int layer)
{
	if (checkLayer(inAnimComp, layer))
		inAnimComp->currrentLayer = layer;
}

void AnimationManager::setFrame(AnimationComponent * inAnimComp, SpriteComponent* inSprite, unsigned int inFrame)
{
	inAnimComp->currrentFrame = inFrame;

	inSprite->mSprite->setTextureRect(sf::IntRect(inAnimComp->currrentFrame * inAnimComp->frameSize.x,
												  inAnimComp->currrentLayer * inAnimComp->frameSize.y,
												  inAnimComp->frameSize.x,
												  inAnimComp->frameSize.y));
}

void AnimationManager::setLayerAndFrame(AnimationComponent * inAnimComp, SpriteComponent * inSprite, unsigned int inLayer, unsigned int inFrame)
{
	setAnimLayer(inAnimComp, inLayer);

	if (checkFrame(inAnimComp, inFrame))
		setFrame(inAnimComp, inSprite, inFrame);
}

void AnimationManager::updateAnim(AnimationComponent * inAnimComp, SpriteComponent * inSprite)
{
	if (inAnimComp->currrentFrame >= inAnimComp->numFrames - 1)
		setFrame(inAnimComp, inSprite, 0);
	else
		setFrame(inAnimComp, inSprite, inAnimComp->currrentFrame + 1);
}

void AnimationManager::updateAnimByInput(SpriteComponent * inSprite, AnimationComponent* inAnimComp, InputComponent * inInput, int inLayer)
{
	if(checkLayer(inAnimComp, inLayer))
		inAnimComp->currrentLayer = inLayer;

	if (inInput->keyS)
		setFrame(inAnimComp, inSprite, DOWN_ANIM);

	else if (inInput->keyW)
		setFrame(inAnimComp, inSprite, UP_ANIM);

	else if (inInput->keyA)
		setFrame(inAnimComp, inSprite, LEFT_ANIM);

	else if (inInput->keyD)
		setFrame(inAnimComp, inSprite, RIGHT_ANIM);
}

bool AnimationManager::checkLayer(AnimationComponent * inAnimComp, int layer)
{
	if (layer >= 0 && layer < inAnimComp->numLayers)
		return true;
	else
		return false;
}

bool AnimationManager::checkFrame(AnimationComponent * inAnimComp, int frame)
{
	if (frame >= 0 && frame < inAnimComp->numFrames)
		return true;
	else
		return false;
}
