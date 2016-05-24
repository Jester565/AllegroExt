#pragma once
#include "ScreenText.h"
#include <string>

namespace AllegroExt
{
	namespace Input
	{
		class TextField
		{
		public:
			TextField();

			TextField(float w, float h);

			void setText(const std::string& str)
			{
				for (int i = 0; i < str.size(); i++)
				{
					text = text.substr(0, wordPos + cursorPos) + (char)str[i] + text.substr(wordPos + cursorPos, text.length());
					changeText(1);
				}
			}

			void set(float w, float h);

			void draw(float x, float y);

			void update(const ALLEGRO_EVENT& ev);

			void clear()
			{
				text.clear();
				cursorPos = 0;
				wordPos = 0;
				cursorX = 0;
				endPos = 0;
			}

			std::string getText()
			{
				return text;
			}

			static TextField* activeField;

			~TextField();
		private:
			AllegroExt::Graphics::ScreenText screenText;

			std::string text;

			float m_x;

			float m_y;

			float m_w;

			float m_h;

			float cursorX;

			int cursorPos;

			int endPos;

			int wordPos;

			int fontSize;

			void mouseSetCursorPos();

			void setCursor(int pos);

			void moveCursor(int change);

			void changeText(int change);

			void updateCursorX();

			void setEndPos();
		};
	}
}
