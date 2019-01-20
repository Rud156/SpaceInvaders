#pragma once
#include "raylib.h"
#include "../Enums/Enums.h"

namespace Utils
{
	class ColorHelpers
	{
	public:

		static float HueToRgb(float hue, float zest, float val);
		static Color HslToRgb(float hue, float saturation, float lightness);

		static Color CollectibleTypeToColor(Enums::BulletType bulletType);
		static Color LerpColor(Color c1, Color c2, float amount);
	};
}
