#include "ExtensionFunctions.h"

namespace Utils
{
	float ExtensionFunctions::Map(float from, float fromMin, float fromMax, float toMin, float toMax)
	{
		const auto fromAbs = from - fromMin;
		const auto fromMaxAbs = fromMax - fromMin;

		const auto normal = fromAbs / fromMaxAbs;

		const auto toMaxAbs = toMax - toMin;
		const auto toAbs = toMaxAbs * normal;

		const auto to = toAbs + toMin;

		return to;
	}

	float ExtensionFunctions::Lerp(float start, float stop, float amount)
	{
		return amount * (stop - start) + start;
	}

	Color ExtensionFunctions::LerpColor(Color c1, Color c2, float amount)
	{
		const auto l0 = Lerp(c1.r, c2.r, amount);
		const auto l1 = Lerp(c1.g, c2.g, amount);
		const auto l2 = Lerp(c1.b, c2.b, amount);
		const auto l3 = Lerp(c1.a, c2.a, amount);

		Color color;
		color.r = l0;
		color.g = l1;
		color.b = l2;
		color.a = l3;

		return color;
	}
}
