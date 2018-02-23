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

			void setHint(const std::string& str);

			void setText(const std::string& str)
			{
				for (int i = 0; i < str.size(); i++)
				{
					text = text.substr(0, wordPos + cursorPos) + (char)str[i] + text.substr(wordPos + cursorPos, text.length());
					changeText(1);
				}
			}

			void set(float w, float h);

			void setAsActiveField()
			{
				activeField = this;
			}

			void draw(float x, float y);

			void update(const ALLEGRO_EVENT& ev);

			bool isEnterPressed()
			{
				return enterPressed;
			}

			void clear()
			{
				text.clear();
				cursorPos = 0;
				wordPos = 0;
				cursorX = 0;
				endPos = 0;
				enterPressed = false;
			}

			std::string reset()
			{
				std::string textCpy = text;
				clear();
				activeField = nullptr;
				return textCpy;
			}

			std::string getText()
			{
				return text;
			}

			bool isActiveField()
			{
				return this == activeField;
			}

			static TextField* activeField;

			void setBackColor(ALLEGRO_COLOR color)
			{
				backColor = color;
			}

			void setTextColor(ALLEGRO_COLOR color)
			{
				textColor = color;
			}

			~TextField();
		private:
			bool enterPressed;

			ALLEGRO_COLOR textColor;

			ALLEGRO_COLOR backColor;

			AllegroExt::Graphics::ScreenText* hint;

			AllegroExt::Graphics::ScreenText screenText;

			std::string text;

			std::string hintText;

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
