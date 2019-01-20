#pragma once
#include "raylib.h"
#include "../Enums/Enums.h"

namespace Utils
{
	class ColorHelpers
	{
	public:

		static int HZVToRGB(int hue, int zest, int val);
		static Color HSLAToRGBA(int h, int saturation, int lightness);

		static Color CollectibleTypeToColor(Enums::BulletType bulletType);
	};
}
