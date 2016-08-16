#pragma once
#include <allegro5/allegro.h>
#include "InputManager.h"
#include "DisplayManager.h"
#include "SoundManager.h"

namespace AllegroExt
{
	class Core
	{
	public:
		Core();
		const static int DEFAULT_FPS_CAP = 60;
		void setFPSCap(int fpsCap)
		{
			this->fpsCap = fpsCap;
		}
		void run();
		static void shutDown();
		static double rate;
		AllegroExt::Sound::SoundManager* getSoundManager()
		{
			return sm;
		}
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
		AllegroExt::Sound::SoundManager* sm;
	private:
		double xScale;
		double yScale;
		int frames;
		int fpsCap;
		bool initEvents();
		double lastTime;
		ALLEGRO_TIMER *timer;
		ALLEGRO_EVENT_QUEUE *timerQueue;
	};
}
