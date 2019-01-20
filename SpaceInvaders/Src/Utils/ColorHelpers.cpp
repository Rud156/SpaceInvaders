#include "ColorHelpers.h"
#include "ExtensionFunctions.h"

namespace Utils
{
	auto ColorHelpers::HZVToRGB(int hue, const int zest, const int val) -> int
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

	Color ColorHelpers::HSLAToRGBA(const int h, const int saturation, const int lightness)
	{
		const auto hue = h * 6;
		const auto sat = saturation;
		const auto li = lightness;

		Color color;

		if (sat == 0)
		{
			color.r = li;
			color.g = li;
			color.b = li;
			color.a = lightness;
		}
		else
		{
			int val;
			if (li < 0.5)
				val = (1 + sat) * li;
			else
				val = li + sat - li * sat;

			const auto zest = 2 * li - val;

			color.r = ColorHelpers::HZVToRGB(hue + 2, zest, val);
			color.g = ColorHelpers::HZVToRGB(hue, zest, val);
			color.b = ColorHelpers::HZVToRGB(hue - 2, zest, val);
			color.a = lightness;
		}

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
