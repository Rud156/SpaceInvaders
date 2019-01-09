#include "pch.h"
#include "ExtensionFunctions.h"

#include <iostream>

namespace Utils {
	float ExtensionFunctions::Map(float from, float fromMin, float fromMax, float toMin, float toMax)
	{
		auto fromAbs = from - fromMin;
		auto fromMaxAbs = fromMax - fromMin;

		auto normal = fromAbs / fromMaxAbs;

		auto toMaxAbs = toMax - toMin;
		auto toAbs = toMaxAbs * normal;

		auto to = toAbs + toMin;

		return to;
	}

	float ExtensionFunctions::Lerp(float start, float stop, float amount)
	{
		return amount * (stop - start) + start;
	}

	Color ExtensionFunctions::LerpColor(Color c1, Color c2, float amount)
	{
		auto l0 = Instance()->Lerp(c1.r, c2.r, amount);
		auto l1 = Instance()->Lerp(c1.g, c2.g, amount);
		auto l2 = Instance()->Lerp(c1.b, c2.b, amount);
		auto l3 = Instance()->Lerp(c1.a, c2.a, amount);

		Color color;
		color.r = l0;
		color.g = l1;
		color.b = l2;
		color.a = l3;

		return color;
	}
}