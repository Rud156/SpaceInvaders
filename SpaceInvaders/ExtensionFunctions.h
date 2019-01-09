#pragma once

#include "raylib.h"

namespace Utils {
	class ExtensionFunctions
	{
	private:
		static ExtensionFunctions *_instance;
		ExtensionFunctions() {}

	public:
		~ExtensionFunctions();
		static ExtensionFunctions *Instance();

		float Map(float from, float fromMin, float fromMax, float toMin, float toMax);
		float Lerp(float start, float stop, float amount);
		Color LerpColor(Color c1, Color c2, float amount);
	};
}