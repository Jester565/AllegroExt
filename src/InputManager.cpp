#include "InputManager.h"
#include "DisplayManager.h"
#include "TextField.h"
#include <iostream> //temp

using namespace AllegroExt::Graphics;
namespace AllegroExt
{
	namespace Input
	{

		InputManager::InputManager()
		{
		}
		
		std::list<char> InputManager::keysPressed;

		int InputManager::mouseX = 0;

		int InputManager::mouseY = 0;

		int InputManager::mouseZ = 0;

		int InputManager::mousePressed = 0;

		int InputManager::mouseClicked = 0;

		ALLEGRO_EVENT_QUEUE* InputManager::inputQueue = nullptr;

		std::vector<ALLEGRO_EVENT> InputManager::events;

		const int InputManager::getPressed()
		{
			return mousePressed;
		}

		const int InputManager::getClicked()
		{
			return mouseClicked;
		}

		bool InputManager::init()
		{
			bool failure = false;
			failure |= !al_install_keyboard();
			failure |= !al_install_mouse();
			inputQueue = al_create_event_queue();
			al_register_event_source(inputQueue, al_get_keyboard_event_source());
			al_register_event_source(inputQueue, al_get_mouse_event_source());
			return !failure;
		}

		bool InputManager::keyPressed(char key)
		{
			if (TextField::activeField != nullptr)
			{
				return false;
			}
			for (auto it = keysPressed.begin(); it != keysPressed.end(); it++)
			{
				if ((*it) == key)
				{
					return true;
				}
			}
			return false;
		}

		bool InputManager::keyTyped(char ev)
		{
			if (TextField::activeField != nullptr)
			{
				return false;
			}
			for (int i = 0; i < events.size(); i++)
			{
				if (ev == events[i].keyboard.unichar)
				{
					return true;
				}
			}
			return false;
		}

		void InputManager::update()
		{
			events.clear();
			mouseClicked = 0;
			ALLEGRO_EVENT ev;
			while (al_get_next_event(inputQueue, &ev))
			{
				switch (ev.type)
				{
				case ALLEGRO_EVENT_MOUSE_AXES:
					mouseX = (ev.mouse.x) / DisplayManager::scaleX + DisplayManager::offX;
					mouseY = (ev.mouse.y) / DisplayManager::scaleY + DisplayManager::offY;
					mouseZ = (ev.mouse.z);
					break;
				case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
					if (ev.mouse.button == 1)
					{
						mousePressed |= MOUSE_LEFT;
					}
					if (ev.mouse.button == 2)
					{
						mousePressed |= MOUSE_RIGHT;
					}
					if (ev.mouse.button == 3)
					{
						mousePressed |= MOUSE_MIDDLE;
					}
					break;
				case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
					if (ev.mouse.button == 1)
					{
						mousePressed ^= MOUSE_LEFT;
						mouseClicked |= MOUSE_LEFT;
					}
					if (ev.mouse.button == 2)
					{
						mousePressed ^= MOUSE_RIGHT;
						mouseClicked |= MOUSE_RIGHT;
					}
					if (ev.mouse.button == 3)
					{
						mousePressed ^= MOUSE_MIDDLE;
						mouseClicked |= MOUSE_MIDDLE;
					}
					break;
				case ALLEGRO_EVENT_KEY_DOWN:
				{
					uint8_t keyVal = (int)ev.keyboard.keycode;
					if (keyVal == (int)ALLEGRO_KEY_SPACE)
					{
						keyVal = 32;
					}
					else
					{
						keyVal += 96;
					}
					keysPressed.push_back((char)keyVal);
					break;
				}
				case ALLEGRO_EVENT_KEY_UP:
				{
					uint8_t keyVal = (int)ev.keyboard.keycode;
					if (keyVal == (int)ALLEGRO_KEY_SPACE)
					{
						keyVal = 32;
					}
					else
					{
						keyVal += 96;
					}
					keysPressed.remove((char)keyVal);
					break;
				}
				case ALLEGRO_EVENT_KEY_CHAR:
					if (TextField::activeField != nullptr)
						TextField::activeField->update(ev);
					events.push_back(ev);
					break;
				default:
					events.push_back(ev);
				}
			}
		}

		InputManager::~InputManager()
		{
			if (inputQueue != nullptr)
			{
				al_destroy_event_queue(inputQueue);
				inputQueue = nullptr;
			}
		}
	}
}