#pragma once
#include <SFML/Graphics.hpp>
#include "Vector2d.h"
// Systems
#include "AnimationManager.h"
#include "CollisionManager.h"
#include "CombatManager.h"
#include "EntityManager.h"
#include "HUDManager.h"
#include "InputManager.h"
#include "InventoryManager.h"
#include "ItemManager.h"
#include "MovementManager.h"
#include "SpriteManager.h"

#include "EntitySpawner.h"

#include "Menu.h"

class Entity;
class TileMap;

class RenderWindow
{
private:
	// Window
	Vector2d windowCenter;
	sf::View playerView;
	unsigned int FPS = 60;
	double camZoom;
	bool bVerticalSyncEnabled = false;

	int frustumTilesX = 6; // Num tiles left AND right from the players position
	int frustumTilesY = 3; // Num tiles up AND down from the players position

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

	void zoomCamera(int zoomAmount);

	// Easy Access
	Entity* mPlayer{ nullptr };
	Vector2d mPlayerLastPos;
	std::shared_ptr<TileMap> mLandscape;

	// Systems
	AnimationManager mAnimationManager;
	CollisionManager mCollisionManager;
	CombatManager mCombatManager;
	EntityManager mEntityManager;
	HUDManager mHUDManager;
	InputManager mInputManager;
	InventoryManager mInventoryManager;
	ItemManager mItemManager;
	MovementManager mMovementManager;
	SpriteManager mSpriteManager;

	EntitySpawner* mEntitySpawner{ nullptr };

	// Menus
	Menu mCraftingMenu;
	Menu mInventoryMenu;
	Menu mEscapeMenu;
};

