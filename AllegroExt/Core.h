#pragma once
#include <allegro5/allegro.h>
#include "InputManager.h"
#include "DisplayManager.h"

namespace AllegroExt
{
	class Core
	{
	public:
		Core();
		void run();
		static void shutDown();
		static double rate;
		~Core();
	protected:
		virtual void setDisplayScales(double xScale, double yScale)
		{
			this->xScale = xScale;
			this->yScale = yScale;
		}
		virtual bool init();
		virtual void draw() = 0;
		static bool running;
		Input::InputManager im;
		AllegroExt::Graphics::DisplayManager dm;
	private:
		double xScale;
		double yScale;
		bool initEvents();
		double lastTime;
		ALLEGRO_TIMER *timer;
		ALLEGRO_EVENT_QUEUE *timerQueue;
	};
}
