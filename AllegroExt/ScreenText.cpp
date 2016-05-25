#include "ScreenText.h"
#include <iostream>
namespace AllegroExt
{
	namespace Graphics
	{
		std::string ScreenText::prePath = "fonts\\";
		std::string ScreenText::defaultFontPath = "Calibri.ttf";

		ScreenText::ScreenText()
			:lastStr("")
		{
			fontPath = defaultFontPath;
			lastFontSize = 0;
			font = nullptr;
		}

		void ScreenText::setDefaultFontPath(std::string path)
		{
			defaultFontPath = path;
		}

		void ScreenText::setFontPath(std::string path)
		{
			fontPath = path;
		}

		int ScreenText::getTextWidth(const std::string& str)
		{
			return al_get_text_width(font, str.c_str());
		}

		void ScreenText::createFont(float size)
		{
			if (size != lastFontSize || font == nullptr)
			{
			  std::cout << "font create called" << std::endl;
			  font = al_load_ttf_font("/home/alex/Program/BB_Server/BeachBoy_Server/BeachBoy_Server/fonts/Calibri.ttf", size, 0);
			  if (font != nullptr)
			  {
			    std::cout << "Font was loaded" << std::endl;
			  }
			  else
			  {
			    std::cout << "Font not loaded" << std::endl;
			  }
				lastFontSize = size;
			}
		}

		void ScreenText::drawText(std::string str, float x, float y, float fontSize, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		{
			if (fontSize != lastFontSize || font == nullptr)
			{
			  createFont(fontSize);
				lastFontSize = fontSize;
			}
			ALLEGRO_COLOR color;
			if (a != UINT8_MAX)
				color = al_map_rgba(r, g, b, a);
			else
				color = al_map_rgb(r, g, b);
			al_draw_text(font, color, x, y, 0, str.c_str());
		}
		
		void ScreenText::drawCenteredText(std::string str, float x, float y, float fontSize, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		{
			if (fontSize != lastFontSize || font == nullptr)
			{
				font = al_load_ttf_font((prePath + fontPath).c_str(), fontSize, 0);
				lastFontSize = fontSize;
				textWidth = al_get_text_width(font, str.c_str());
				lastStr = str;
			}
			if (lastStr != str)
			{
				textWidth = al_get_text_width(font, str.c_str());
				lastStr = str;
			}
			ALLEGRO_COLOR color;
			if (a != UINT8_MAX)
				color = al_map_rgba(r, g, b, a);
			else
				color = al_map_rgb(r, g, b);
			al_draw_text(font, color, x - textWidth/2, y, 0, str.c_str());
		}

		ScreenText::~ScreenText()
		{
		}
	}
}
