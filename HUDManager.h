#pragma once

#include <vector>

class Vector2d;
struct HUDComponent;

class HUDManager
{
public:
	HUDManager();
	~HUDManager();
	
	void setFont(HUDComponent* hudComp, const std::string * fontPath);
	void buildHUDComponent(HUDComponent* hudComp);
	void updateHUDPosition(std::vector<HUDComponent*>* hudComps, Vector2d* newPos);
	void updateHUDText(HUDComponent* hudComps, std::string newText);
};

