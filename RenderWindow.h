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
#include "SpriteManager.h"

class Entity;
class TileMap;

class RenderWindow
{
private:
	// Window
	Vector2d windowCenter;
	sf::View playerView;
	unsigned int FPS = 60;
	bool bVerticalSyncEnabled = false;
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
	std::shared_ptr<TileMap> mLandscape;

	// Systems
	AnimationManager mAnimationManager;
	CollisionManager mCollisionManager;
	CombatManager mCombatManager;
	EntityManager mEntityManager;
	InputManager mInputManager;
	InventoryManager mInventoryManager;
	MovementManager mMovementManager;
	SpriteManager mSpriteManager;
};

