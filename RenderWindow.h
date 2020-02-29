#pragma once
#include <SFML/Graphics.hpp>
#include "Vector2d.h"
// Systems
#include "AnimationManager.h"
#include "CollisionManager.h"
#include "CombatManager.h"
#include "EntityManager.h"
#include "EntityRenderer.h"
#include "HUDManager.h"
#include "InputManager.h"
#include "InventoryManager.h"
#include "ItemManager.h"
#include "LightManager.h"
#include "MovementManager.h"
#include "SpriteManager.h"

#include "EntitySpawner.h"
#include "StateMachine.h"

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
	bool bNightEnabled = false;

	int frustumTilesX = 6; // Num tiles left AND right from the players position
	int frustumTilesY = 3; // Num tiles up AND down from the players position

	sf::Shader mShaders[1];

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
	void draw(float deltaTime);
	void zoomCamera(int zoomAmount);

	void toggleNight();

	// Easy Access
	Entity* mPlayer{ nullptr };
	Vector2d mPlayerLastPos;
	std::shared_ptr<TileMap> mLandscape;

	// Systems
	AnimationManager mAnimationManager;
	CollisionManager mCollisionManager;
	CombatManager mCombatManager;
	EntityRenderer mEntityRenderer;
	HUDManager mHUDManager;
	InputManager mInputManager;
	InventoryManager mInventoryManager;
	ItemManager mItemManager;
	LightManager mLightManager;
	MovementManager mMovementManager;
	SpriteManager mSpriteManager;

	EntityManager* mEntityManager{ nullptr };
	EntitySpawner* mEntitySpawner{ nullptr };
	StateMachine* mStateMachine{ nullptr };

	// Menus
	Menu mCraftingMenu;
	Menu mInventoryMenu;
	Menu mEscapeMenu;
};

