#include "ScreenText.h"
#include <iostream>
namespace AllegroExt
{
	namespace Graphics
	{
		std::string ScreenText::FONT_DEFAULT = "Calibri.ttf";

		std::vector <FontContainer*> ScreenText::Fonts = std::vector <FontContainer*>();

		FontContainer::FontContainer(const std::string& fontName, float size)
			:fontName(fontName), fontSize(size), count(1), allegroFont(nullptr)
		{
			allegroFont = al_load_ttf_font(fontName.c_str(), size, 0);
		}

		void ScreenText::DecrementFont(const std::string& name, float size)
		{
			for (int i = 0; i < Fonts.size(); i++)
			{
				if (Fonts.at(i)->match(name, size))
				{
					Fonts.at(i)->count--;
					if (Fonts.at(i)->count <= 0)
					{
						delete Fonts.at(i);
						Fonts.erase(Fonts.begin() + i);
						std::cout << "FONT DELETED: " << name << " " << size << " :" << Fonts.size() << std::endl;
					}
					return;
				}
			}
		}

		ALLEGRO_FONT* ScreenText::GetFont(const std::string& name, float size)
		{
			for (int i = 0; i < Fonts.size(); i++)
			{
				if (Fonts.at(i)->match(name, size))
				{
					Fonts.at(i)->count++;
					return Fonts.at(i)->getFont();
				}
			}
			Fonts.push_back(new FontContainer(name, size));
			std::cout << "FONT ADDED: " << name << " " << size << " :" << Fonts.size() << std::endl;
			return Fonts.at(Fonts.size() - 1)->getFont();
		}

		ScreenText::ScreenText()
			:lastFontSize(0), fontName(FONT_DEFAULT), font(nullptr)
		{

		}

		ScreenText::ScreenText(ScreenText& st)
		{
			font = nullptr;
			lastFontSize = st.lastFontSize;
			fontName = st.fontName;
			if (lastFontSize != 0)
			{
				createFont(lastFontSize);
			}
		}

		void ScreenText::SetDefaultFont(const std::string& path)
		{
			FONT_DEFAULT = path;
		}

		void ScreenText::setFontName(const std::string& name)
		{
			fontName = name;
			createFont(lastFontSize);
		}

		int ScreenText::getTextWidth(const std::string& str)
		{
			if (font != nullptr)
			{
				return al_get_text_width(font, str.c_str());
			}
			return 0;
		}

		void ScreenText::createFont(float size)
		{
			if (font != nullptr)
			{
				DecrementFont(fontName, lastFontSize);
				font = nullptr;
			}
			font = GetFont(fontName, size);
			lastFontSize = size;
		}

		void ScreenText::drawText(const std::string& str, float x, float y, float fontSize, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		{
			if (fontSize != lastFontSize || font == nullptr)
			{
				createFont(fontSize);
			}
			ALLEGRO_COLOR color;
			if (a != UINT8_MAX)
				color = al_map_rgba(r, g, b, a);
			else
				color = al_map_rgb(r, g, b);
			al_draw_text(font, color, x, y, 0, str.c_str());
		}
		
		void ScreenText::drawCenteredText(const std::string& str, float x, float y, float fontSize, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		{
			if (fontSize != lastFontSize || font == nullptr)
			{
				createFont(fontSize);
			}
			ALLEGRO_COLOR color;
			if (a != UINT8_MAX)
				color = al_map_rgba(r, g, b, a);
			else
				color = al_map_rgb(r, g, b);
			al_draw_text(font, color, x, y, ALLEGRO_ALIGN_CENTER, str.c_str());
		}

		ScreenText::~ScreenText()
		{
			if (font != nullptr)
			{
				DecrementFont(fontName, lastFontSize);
				font = nullptr;
			}
		}
	}
}
