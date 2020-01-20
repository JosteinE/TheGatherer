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
class TileMap;

class RenderWindow
{
private:
	// Window
	Vector2d windowCenter;
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

	// Easy Access
	Entity* mPlayer{ nullptr };
	sf::VertexArray* triangle{ nullptr };
	TileMap* mLandscape{ nullptr };

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

