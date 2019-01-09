#pragma once

#include "raylib.h"

namespace Utils {
	static class ExtensionFunctions
	{
	public:
		static float Map(float from, float fromMin, float fromMax, float toMin, float toMax);
		static float Lerp(float start, float stop, float amount);
		static Color LerpColor(Color c1, Color c2, float amount);
	};
}