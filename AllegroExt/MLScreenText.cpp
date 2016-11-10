#include "MLScreenText.h"

namespace AllegroExt
{
	namespace Graphics
	{
		bool TextHeightCallBack(int lineNum, const char* line, int size, void* countVP)
		{
			int* count = static_cast <int*>(countVP);
			(*count)++;
			return true;
		}

		MLScreenText::MLScreenText()
			:ScreenText(), maxWidth(1000), lhScale(1.2)
		{

		}

		void MLScreenText::drawText(const std::string & str, float x, float y, float fontSize, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
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
			al_draw_multiline_text(font, color, x, y, maxWidth, fontSize * lhScale, ALLEGRO_ALIGN_LEFT, str.c_str());
		}

		void MLScreenText::drawCenteredText(const std::string & str, float x, float y, float fontSize, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
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
			al_draw_multiline_text(font, color, x, y, maxWidth, fontSize * lhScale, ALLEGRO_ALIGN_CENTRE, str.c_str());
		}

		float MLScreenText::getTextHeight(const std::string & str, float w, float fontSize)
		{
			if (fontSize != lastFontSize || font == nullptr)
			{
				createFont(fontSize);
			}
			int count = 0;
			al_do_multiline_text(font, w, str.c_str(), &TextHeightCallBack, (void*)(&count));
			return count * fontSize * lhScale;
		}

		MLScreenText::~MLScreenText()
		{
		}
	}
}
