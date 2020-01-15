#pragma once
#include <SFML/Graphics.hpp>
#include "Vector2d.h"

// World details
#include "WorldComponent.h"

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
public:
	// Construct the window
	RenderWindow();
	~RenderWindow();

	// Pointer to the window
	sf::RenderWindow* mWindow;

	// Details regarding the world structure
	WorldComponent mWorld;

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

