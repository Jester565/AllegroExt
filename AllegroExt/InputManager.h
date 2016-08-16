#pragma once
#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 4
#include <allegro5/allegro.h>
#include <string>
#include <vector>
#include <list>

namespace AllegroExt
{
	namespace Input
	{
		class InputManager
		{
		public:
			InputManager();
			bool init();
			void update();
			static bool keyPressed(char key);
			static bool keyTyped(char ev);
			static int mouseX, mouseY, mouseZ;
			static const int getPressed();
			static const int getClicked();
			~InputManager();
		private:
			static ALLEGRO_EVENT_QUEUE* inputQueue;
			static std::vector <ALLEGRO_EVENT> events;
			static std::list <char> keysPressed;
			static int mousePressed;
			static int mouseClicked;
		};
	}
}
