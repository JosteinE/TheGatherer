#pragma once
#include <SFML/Graphics.hpp>
#include "Vector2d.h"

// Systems
#include "AnimationManager.h"
#include "CollisionManager.h"
#include "CombatManager.h"
#include "EntityManager.h"
#include "InputManager.h"
#include "InventoryManager.h"
#include "MovementManager.h"
#include "ShapeManager.h"

class Entity;

class RenderWindow
{
private:
	Vector2d mWindowCenter;
	float viewSize = 75; // % of how much of the landscape should be visible relative to the window size.
	sf::View playerView;
public:
	// Construct the window
	RenderWindow();
	~RenderWindow();

	// Pointer to the window
	sf::RenderWindow* mWindow;

	// Map / Tiles 
	Vector2d tileSize{ 75.f, 75.f };
	Vector2d tileSetSize{ 50, 50 };
	Vector2d tileSpacing{ 2, 2 };

	// Builds the scene
	void init();

	// Runs the game
	void tick(float deltaTime);

	// Temp
	Entity* mPlayer{ nullptr };
	std::vector<Entity*> mTiles;

	// Systems
	AnimationManager mAnimationManager;
	CollisionManager mCollisionManager;
	CombatManager mCombatManager;
	EntityManager mEntityManager;
	InputManager mInputManager;
	InventoryManager mInventoryManager;
	MovementManager mMovementManager;
	ShapeManager mShapeManager;
};

