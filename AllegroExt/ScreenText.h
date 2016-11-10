#pragma once
#include "Core.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include <map>

namespace AllegroExt
{
	namespace Graphics
	{
		struct FontContainer
		{
		public:
			FontContainer(const std::string& fontName, float size);

			ALLEGRO_FONT* getFont()
			{
				return allegroFont;
			}

			bool match(const std::string& name, float size)
			{
				return (fontName == name && fontSize == size);
			}

			int count;

			~FontContainer()
			{
				if (allegroFont != nullptr)
				{
					al_destroy_font(allegroFont);
					allegroFont = nullptr;
				}
			}

		private:
			ALLEGRO_FONT* allegroFont;
			std::string fontName;
			float fontSize;
		};
		class ScreenText
		{
		public:
			ScreenText();
			ScreenText(ScreenText& st);
			static std::string FONT_DEFAULT;
			static std::vector <FontContainer*> Fonts;
			static void DecrementFont(const std::string& name, float size);
			static void SetDefaultFont(const std::string& path);
			static ALLEGRO_FONT* GetFont(const std::string& name, float size);

			virtual void setFontName(const std::string& name);

			virtual void drawText(const std::string& str, float x, float y, float fontSize, uint8_t = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = UINT8_MAX);

			virtual void drawCenteredText(const std::string& str, float x, float y, float fontSize, uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = UINT8_MAX);

			virtual int getTextWidth(const std::string& str);

			void createFont(float size);

			virtual ~ScreenText();
		protected:
			std::string fontName;
			float lastFontSize;
			ALLEGRO_FONT* font;
		};
	}
}
