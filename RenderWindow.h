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
class GameStateComponent;

class RenderWindow
{
private:
	// Window
	Vector2d windowCenter;
	sf::View playerView;
	unsigned int FPS = 60;
	double camZoom;
	bool bVerticalSyncEnabled = false;

	bool spawnNightMonsters = true;

	int frustumTilesWidth = 6; // Num tiles left AND right from the players position
	int frustumTilesHeight = 3; // Num tiles up AND down from the players position

	sf::Shader mShaders[1];
	bool bContEnvLightUpdate{ false };

	unsigned int timeTickRate = 3600; // what the seconds will be multiplied with in game
	unsigned int elapsedTimeSeconds = 0;
	unsigned int mCurrentHour = 0;

public:
	// Construct the window
	RenderWindow();
	~RenderWindow();

	// Pointer to the window
	sf::RenderWindow* mWindow{ nullptr };

	// Builds the scene
	void initNewGame();

	// Runs the game
	void tick(float deltaTime);
	void draw(float deltaTime);
	void zoomCamera(int zoomAmount);

	void addSeconds(int seconds, float deltaTime = 0.f);
	unsigned int getElapsedTime() const;
	void printTime();

	void leftMouseButton(GameStateComponent* inComp);
	void rightMouseButton(GameStateComponent* inComp);

	void deleteGame();
	void resetGame();
	void saveGame();
	void loadGame();

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
};

