#include "Core.h"
#include <iostream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

namespace AllegroExt
{
	bool Core::running = true;

	double Core::rate = 1;

	void Core::shutDown()
	{
		running = false;
	}

	Core::Core()
		:lastTime(0), xScale(1), yScale(1), timer(nullptr), timerQueue(nullptr)
	{
		
	}

	bool Core::init()
	{
		bool failure = false;
		failure |= !al_init();	//initialize allegro API
		if (failure)
		{
			std::cout << "FAIL" << std::endl;
		}
		failure |= !al_init_image_addon();
		failure |= !al_init_font_addon();
		failure |= !al_init_ttf_addon();
		failure |= !al_init_primitives_addon();
		failure |= !im.init();	//initialize inputManager
		failure |= !initEvents();
		failure |= !dm.init(xScale, yScale);	//create display
		return !failure;
	}

	void Core::run()
	{
		if (init())
		{
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
		timer = al_create_timer(1.0 / 60.0);
		timerQueue = al_create_event_queue();
		al_register_event_source(timerQueue, al_get_timer_event_source(timer));
		al_start_timer(timer);
		return timer != nullptr;
	}

	Core::~Core()
	{

	}
}
