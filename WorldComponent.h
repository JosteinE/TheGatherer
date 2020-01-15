#pragma once
struct WorldComponent
{
	// Window
	Vector2d windowCenter;
	sf::View playerView;
	float viewSize = 75; // % of how much of the landscape should be visible relative to the window size.

	// Map / Tiles 
	Vector2d tileSize{ 75.f, 75.f };
	Vector2d tileSetSize{ 50, 50 };
	Vector2d tileSpacing{ 1.1f, 1.1f };
};