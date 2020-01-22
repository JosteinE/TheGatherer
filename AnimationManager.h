#pragma once
#include "Vector2d.h"
struct AnimationComponent;
struct SpriteComponent;
struct InputComponent;

enum PLAYERANIM // Corresponds with the order of frames defined by the player sprite sheet
{
	UP_ANIM = 0,
	LEFT_ANIM = 1,
	DOWN_ANIM = 2,
	RIGHT_ANIM = 3
};

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

