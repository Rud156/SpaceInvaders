#include "ColorHelpers.h"
#include "ExtensionFunctions.h"

namespace Utils
{
	float ColorHelpers::HueToRgb(float hue, const float zest, const float val)
	{
		if (hue < 0)
			hue += 6;
		else if (hue >= 6)
			hue -= 6;
		if (hue < 1)
			return zest + (val - zest) * hue;
		else if (hue < 3)
			return val;
		else if (hue < 4)
			return zest + (val - zest) * (4 - hue);
		else
			return zest;
	}

	Color ColorHelpers::HslToRgb(float hue, const float saturation, const float lightness)
	{
		Color color;
		float val;

		hue /= 60.0f;

		if (lightness <= 0.5f)
			val = lightness * (saturation + 1);
		else
			val = lightness + saturation - (lightness * saturation);
		const auto zest = lightness * 2.0f - val;

		color.r = HueToRgb(hue + 2, zest, val) * 255;
		color.g = HueToRgb(hue, zest, val) * 255;
		color.b = HueToRgb(hue - 2, zest, val) * 255;
		color.a = 255;

		return color;
	}

	Color ColorHelpers::CollectibleTypeToColor(const Enums::BulletType bulletType)
	{
		switch (bulletType)
		{
		case Enums::BulletType::SingleBullet:
			return RED;

		case Enums::BulletType::DoubleBullet:
			return GREEN;

		case Enums::BulletType::SprayBullet:
			return BLUE;

		default:
			return RAYWHITE;
		}
	}

	Color ColorHelpers::LerpColor(const Color c1, const Color c2, const float amount)
	{
		const auto l0 = ExtensionFunctions::Lerp(c1.r, c2.r, amount);
		const auto l1 = ExtensionFunctions::Lerp(c1.g, c2.g, amount);
		const auto l2 = ExtensionFunctions::Lerp(c1.b, c2.b, amount);
		const auto l3 = ExtensionFunctions::Lerp(c1.a, c2.a, amount);

		Color color;
		color.r = l0;
		color.g = l1;
		color.b = l2;
		color.a = l3;

		return color;
	}
}
