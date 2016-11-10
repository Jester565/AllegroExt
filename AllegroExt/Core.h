#pragma once
#include <allegro5/allegro.h>
#include "InputManager.h"
#include "DisplayManager.h"
#include "SoundManager.h"
#include <string>

namespace AllegroExt
{
	static std::string ResourcePath;
	class Core
	{
	public:
		Core(const std::string& resourcePath);
		const static int DEFAULT_FPS_CAP = 60;
		void setFPSCap(int fpsCap)
		{
			this->fpsCap = fpsCap;
		}
		void run();
		static void shutDown();
		static double rate;
		static AllegroExt::Sound::SoundManager* GetSoundManager()
		{
			return SoundManager;
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
		static AllegroExt::Sound::SoundManager* SoundManager;
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
