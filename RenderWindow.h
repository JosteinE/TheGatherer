#pragma once
#include <SFML/Graphics.hpp>

// Systems
#include "AnimationManager.h"
#include "CollisionManager.h"
#include "CombatManager.h"
#include "InputManager.h"
#include "InventoryManager.h"
#include "MovementManager.h"
#include "ShapeManager.h"

class Entity;

class RenderWindow
{
private:
	sf::Vector2f mWindowCenter;
	float viewSize = 75; // % of how much of the landscape should be visible relative to the window size.
	sf::View playerView;
public:
	// Construct the window
	RenderWindow();
	~RenderWindow();

	// Pointer to the window
	sf::RenderWindow* mWindow;

	// Builds the scene
	void init();

	// Runs the game
	void tick(float deltaTime);

	// Temp
	Entity* mPlayer{ nullptr };
	std::vector<sf::RectangleShape*> mTiles;

	// Systems
	AnimationManager mAnimationManager;
	CollisionManager mCollisionManager;
	CombatManager mCombatManager;
	InputManager mInputManager;
	InventoryManager mInventoryManager;
	MovementManager mMovementManager;
	ShapeManager mShapeManager;
};

