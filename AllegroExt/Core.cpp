#include "Core.h"
#include <iostream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <Windows.h>

namespace AllegroExt
{
	bool Core::running = false;

	double Core::rate = 1;

	AllegroExt::Sound::SoundManager* Core::SoundManager = nullptr;

	void Core::shutDown()
	{
		running = false;
	}

	Core::Core(const std::string& resourcePath)
		:lastTime(0), xScale(1), yScale(1), fpsCap(DEFAULT_FPS_CAP), timer(nullptr), timerQueue(nullptr), frames(0)
	{
		ResourcePath = resourcePath;
	}

	bool Core::init()
	{
		SoundManager = new AllegroExt::Sound::SoundManager();
		bool failure = false;
		failure |= !al_init();	//initialize allegro API
		failure |= !al_init_image_addon();
		failure |= !al_init_font_addon();
		failure |= !al_init_ttf_addon();
		failure |= !al_init_primitives_addon();
		failure |= !SoundManager->init();
		failure |= !im.init();	//initialize inputManager
		failure |= !initEvents();
		failure |= !dm.init(xScale, yScale);	//create display
		if (failure)
		{
			std::cout << "FAIL of AllegroExt initialization" << std::endl;
			system("pause");
		}
		else
		{
			uint32_t version = al_get_allegro_version();
			int major = version >> 24;
			int minor = (version >> 16) & 0xff;
			int revision = (version >> 8) & 0xff;
			int release = (version) & 0xff;
			std::cout << "ALLEGRO CORE INTIALIZED: " << major << "." << minor << "." << revision << "." << release << std::endl;
		}
		return !failure;
	}

	void Core::run()
	{
		if (init())
		{
			running = true;
			std::cout << "Init Sucessful" << std::endl;
			ALLEGRO_EVENT ev;
			while (running)
			{
				al_wait_for_event(timerQueue, &ev);
				rate = (al_current_time() - lastTime) * 60;
				lastTime = al_current_time();
				dm.update();
				im.update();
				draw();
			}
		}
		else
		{
			std::cout << "Init failed" << std::endl;
		}
	}

	bool Core::initEvents()
	{
		timer = al_create_timer(1.0 / fpsCap);
		timerQueue = al_create_event_queue();
		al_register_event_source(timerQueue, al_get_timer_event_source(timer));
		al_start_timer(timer);
		return timer != nullptr;
	}

	Core::~Core()
	{
		if (timer != nullptr)
		{
			al_destroy_timer(timer);
			timer = nullptr;
		}
		if (timerQueue != nullptr)
		{
			al_destroy_event_queue(timerQueue);
		}
	}
}
