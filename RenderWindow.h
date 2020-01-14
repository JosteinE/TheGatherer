#pragma once
// Systems
#include "AnimationManager.h"
#include "CollisionManager.h"
#include "CombatManager.h"
#include "InputManager.h"
#include "InventoryManager.h"
#include "MovementManager.h"
#include "ShapeManager.h"

#include "Entity.h"

class RenderWindow
{
private:
	sf::Vector2f mWindowCenter;
public:
	RenderWindow();
	~RenderWindow();

	// builds the scene
	void init(sf::Vector2f windowCenter);

	// runs the game
	void tick(float deltaTime, InputComponent* inputComponent);

	//Temp
	Entity* mPlayer{ nullptr };
	std::vector<sf::RectangleShape*> mTiles;

	//Systems
	AnimationManager mAnimationManager;
	CollisionManager mCollisionManager;
	CombatManager mCombatManager;
	InputManager mInputManager;
	InventoryManager mInventoryManager;
	MovementManager mMovementManager;
	ShapeManager mShapeManager;
};

