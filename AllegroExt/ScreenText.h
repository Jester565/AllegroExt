#pragma once
#include <string>
#include "Core.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

namespace AllegroExt
{
	namespace Graphics
	{
		class ScreenText
		{
		public:
			ScreenText();

			static void setDefaultFontPath(std::string path);

			void setFontPath(std::string path);

			void drawText(std::string str, float x, float y, float fontSize, uint8_t = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = UINT8_MAX);

			void drawCenteredText(std::string str, float x, float y, float fontSize, uint8_t = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = UINT8_MAX);

			int getTextWidth(const std::string& str);

			void createFont(float size);

			~ScreenText();
		private:
			static std::string defaultFontPath;
			static std::string prePath;
			std::string fontPath;
			std::string lastStr;
			float lastFontSize;
			int textWidth = 0;
			ALLEGRO_FONT* font;
		};
	}
}
