#pragma once
#define STANDARD_WIDTH 1920.0
#define STANDARD_HEIGHT 1080.0

#include <allegro5/allegro.h>
#include <vector>

namespace AllegroExt
{
	namespace Graphics
	{
		const int WINDOW_X = 1920;

		const int WINDOW_Y = 1080;

		class DisplayManager
		{
		public:
			DisplayManager();

			bool init(double wScale = 1, double hScale = 1);

			void update();

			void changeWindowRect(int x, int y, double wScale, double hScale);

			bool eventOccured(int);

			static float scaleX;

			static float scaleY;

			static float offX;

			static float offY;

			~DisplayManager();
		private:
			static ALLEGRO_DISPLAY* display;
			static ALLEGRO_EVENT_QUEUE* displayQueue;
			static std::vector <ALLEGRO_EVENT> events;
			int getTaskBarHeight();
			void updateEventList();
			int screenWidth;
			int screenHeight;
			bool sizeUpdated;
		};
	}
}
