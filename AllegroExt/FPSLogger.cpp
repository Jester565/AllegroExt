#include "FPSLogger.h"
#include "ShapeRenderer.h"
#include <allegro5/allegro.h>

namespace AllegroExt
{
	FPSLogger::FPSLogger(double updateRate)
		:callCount(0), fps("0"), lastTime(0)
	{
		st = new Graphics::ScreenText();
	}

	void FPSLogger::draw(float x, float y, float fontSize)
	{
		if (al_current_time() - lastTime >= 1.0)
		{
			fps = std::to_string(callCount);
			callCount = 0;
			lastTime = al_current_time();
		}
		else
		{
			callCount++;
		}
		Graphics::ShapeRenderer::drawRectangle(x, y, fontSize * 2, fontSize, 0, 0, 0, 100);
		st->drawText(fps, x, y, fontSize, 255, 255, 255, 255);
	}

	FPSLogger::~FPSLogger()
	{
		delete st;
		st = nullptr;
	}
}
