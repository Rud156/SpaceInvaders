#include "ColorHelpers.h"

namespace Utils
{
	int ColorHelpers::HZVToRGB(int hue, int zest, int val)
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
}
