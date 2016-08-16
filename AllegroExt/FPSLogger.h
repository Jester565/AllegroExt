#pragma once
#include "ScreenText.h"
#include <string>

namespace AllegroExt
{
	class FPSLogger
	{
	public:
		FPSLogger(double updateRate = 1);

		void draw(float x, float y, float fontSize);

		~FPSLogger();

		double lastTime;
		Graphics::ScreenText* st;
		std::string fps;
		int callCount;
	};
}

