#include "HUDManager.h"
#include "Vector2d.h"
#include "HUDComponent.h"


HUDManager::HUDManager()
{
}


HUDManager::~HUDManager()
{
}

void HUDManager::buildHUDComponent(HUDComponent * hudComp)
{
	if (!hudComp->mFont.loadFromFile(hudComp->fontPath))
		std::cout << "Could not load font." << std::endl;
	else
		hudComp->mText.setFont(hudComp->mFont);
	hudComp->mText.setString(hudComp->initialText);
	hudComp->mText.setCharacterSize(hudComp->characterSize);
	hudComp->mText.setScale(hudComp->textSize, hudComp->textSize);
	hudComp->mText.setPosition(hudComp->textRelativePos.x, hudComp->textRelativePos.y);
	hudComp->mText.setFillColor(hudComp->textColour);
	if (hudComp->bBold)
		hudComp->mText.setStyle(sf::Text::Bold);
}

void HUDManager::updateHUDPosition(std::vector<HUDComponent*>* hudComps, Vector2d * newPos)
{
	for(HUDComponent *comp : *hudComps)
		comp->mText.setPosition(comp->textRelativePos.x + newPos->x, comp->textRelativePos.y + newPos->y);
}

void HUDManager::updateHUDText(HUDComponent* hudComps, std::string newText)
{
	hudComps->mText.setString(newText);
}
