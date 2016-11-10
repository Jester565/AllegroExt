#include "DisplayManager.h"
#include "Core.h"
#include <allegro5/allegro.h>
#ifdef _WIN32
#include <allegro5/allegro_windows.h>
#include <Windows.h>
#endif
#include <iostream>

using namespace AllegroExt;

namespace AllegroExt
{
	namespace Graphics
	{
	  #ifdef _WIN32
		float DisplayManager::scaleX = 1;

		float DisplayManager::scaleY = 1;
	  #else
	  float DisplayManager::scaleX = 1366.0/1920.0;
	  float DisplayManager::scaleY = 768.0/1080.0;
	  #endif
		float DisplayManager::offX = 0;

		float DisplayManager::offY = 0;

		std::vector<ALLEGRO_EVENT> DisplayManager::events;

		ALLEGRO_EVENT_QUEUE* DisplayManager::displayQueue = nullptr;

		ALLEGRO_DISPLAY* DisplayManager::display = nullptr;

		DisplayManager::DisplayManager()
		{
			sizeUpdated = false;
		}

		bool DisplayManager::init(double wScale, double hScale)
		{
            screenWidth = WINDOW_X;
            screenHeight = WINDOW_Y;
            #ifdef _WIN32
            RECT desktop;
			const HWND hDesktop = GetDesktopWindow();
			GetWindowRect(hDesktop, &desktop);
			screenWidth = desktop.right;
			screenHeight = desktop.bottom;
			#endif
			al_set_new_display_flags(ALLEGRO_RESIZABLE | ALLEGRO_WINDOWED | ALLEGRO_PROGRAMMABLE_PIPELINE);
			al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);	//enable anti-aliasing
			al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
			display = al_create_display(WINDOW_X, WINDOW_Y);	//create display
			if (display == nullptr)
			{
				return display;
			}
			#ifdef _WIN32
			MoveWindow(al_get_win_window_handle(display), 0, 0, screenWidth * wScale, (screenHeight * hScale) - getTaskBarHeight(), false);
			if (wScale == 1 && hScale == 1)
			{
				ShowWindow(al_get_win_window_handle(display), SW_MAXIMIZE);	//maximize window
			}
			#endif
			al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
			displayQueue = al_create_event_queue();
			al_register_event_source(displayQueue, al_get_display_event_source(display));
			return display != nullptr && displayQueue != nullptr;
		}
                #ifdef _WIN32
		void DisplayManager::changeWindowRect(int x, int y, double wScale, double hScale)
		{
			if (display != nullptr)
			{
				MoveWindow(al_get_win_window_handle(display), 0, 0, screenWidth * wScale, (screenHeight * hScale) - getTaskBarHeight(), false);
			}
		}
	        
		int DisplayManager::getTaskBarHeight()
		{
			RECT rect;
			HWND taskBar = FindWindowA((LPCSTR)"Shell_traywnd", NULL);
			if (taskBar && GetWindowRect(taskBar, &rect))
			{
				return rect.bottom - rect.top;
			}
			return 0;
		}
	        #endif

		bool DisplayManager::eventOccured(int ev)
		{
			for (int i = 0; i < events.size(); i++)
				if (events[i].type == ev)
					return true;
			return false;
		}

		void DisplayManager::update()
		{
			ALLEGRO_COLOR blue = al_map_rgb(200, 200, 255);
			updateEventList();
			if (eventOccured(ALLEGRO_EVENT_DISPLAY_CLOSE))
			{
				Core::shutDown();
			}
			else if (eventOccured(ALLEGRO_EVENT_DISPLAY_RESIZE) || !sizeUpdated)
			{
			  #ifdef _WIN32
				RECT rect;
				if (GetClientRect(al_get_win_window_handle(display), &rect))
				{
					/*
					std::cout << "RESIZED" << std::endl;
					al_acknowledge_resize(display);
					ALLEGRO_TRANSFORM trans;
					al_identity_transform(&trans);
					al_scale_transform(&trans, (rect.right - rect.left) / 1920.0, (rect.bottom - rect.top) / 1080.0);
					al_use_transform(&trans);
					*/
					scaleX = (rect.right - rect.left) / (STANDARD_WIDTH);
					scaleY = (rect.bottom - rect.top) / (STANDARD_HEIGHT);
				}
				sizeUpdated = true;
			  #else
				al_acknowledge_resize(display);
				ALLEGRO_TRANSFORM trans;
				al_identity_transform(&trans);
				al_scale_transform(&trans, 1300.0/1920.0, 750.0/1080.0);
				al_use_transform(&trans);
			  #endif
			}
			al_flip_display();
			al_clear_to_color(blue);
		}

		void DisplayManager::updateEventList()
		{
			events.clear();
			ALLEGRO_EVENT ev;
			while (al_get_next_event(displayQueue, &ev))
			{
				events.push_back(ev);
			}
		}

		DisplayManager::~DisplayManager()
		{
			events.clear();
			if (display != nullptr)
			{
				//al_destroy_display(display);
				display = nullptr;
			}
			if (displayQueue != nullptr)
			{
				al_destroy_event_queue(displayQueue);
				displayQueue = nullptr;
			}
		}
	}
}
