#pragma once
#include "Vector2d.h"
struct AnimationComponent;
struct SpriteComponent;
struct InputComponent;

class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();
	void buildAnim(AnimationComponent* inAnimComp, SpriteComponent* inSprite, Vector2d frameSize);
	void setAnimLayer(AnimationComponent* inAnimComp, unsigned int layer);
	void setFrame(AnimationComponent* inAnimComp, SpriteComponent* inSprite, unsigned int inFrame);
	void setLayerAndFrame(AnimationComponent* inAnimComp, SpriteComponent* inSprite, unsigned int inLayer, unsigned int inFrame);
	void updateAnim(AnimationComponent* inAnimComp, SpriteComponent* inSprite);
	void updateAnimByInput(SpriteComponent* inSprite, AnimationComponent* inAnimComp, InputComponent* inInput, int inLayer = -1);

private:
	bool checkLayer(AnimationComponent* inAnimComp, int layer);
	bool checkFrame(AnimationComponent* inAnimComp, int frame);
};

