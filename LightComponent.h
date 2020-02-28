#pragma once

struct LightComponent
{
	float ambientStrength{ -1.f };
	float ambientColour[3]{ 0.3f, 0.3f, 0.3f };
	float lightStrength{ 2.f };
	float lightColour[3]{ 0.3f, 0.3f, 0.3f };
};