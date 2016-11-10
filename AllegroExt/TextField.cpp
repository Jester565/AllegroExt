#include "TextField.h"
#include "Button.h"
#include <iostream>

using namespace AllegroExt::Graphics;
using namespace AllegroExt::Input;

namespace AllegroExt
{
	namespace Input
	{
		TextField* TextField::activeField = nullptr;

		TextField::TextField()
			:enterPressed(false), mouseAFSet(true)
		{
			backColor = al_map_rgba(200, 200, 200, 255);
			textColor = al_map_rgba(10, 0, 255, 255);
		}

		TextField::TextField(float w, float h)
		{
			backColor = al_map_rgba(200, 200, 200, 255);
			textColor = al_map_rgba(10, 0, 255, 255);
			set(w, h);
		}

		void TextField::set(float w, float h)
		{
			m_w = w;
			m_h = h;
			cursorPos = 0;
			wordPos = 0;
			cursorX = 0;
			endPos = 0;
			fontSize = (int)(h * .7);
			screenText.createFont(fontSize);
		}

		void TextField::update(const ALLEGRO_EVENT& ev)
		{
			const int inputChar = ev.keyboard.unichar;
			if (ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && text.length() > 0)
			{
				if (wordPos + cursorPos > 0)
				{
					text = text.substr(0, wordPos + cursorPos - 1) + text.substr(wordPos + cursorPos, text.length());
					changeText(-1);
				}
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT)
			{
				moveCursor(-1);
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT)
			{
				moveCursor(1);
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER)
			{
				enterPressed = true;
			}
			else if (inputChar >= 32 && inputChar <= 125)
			{
				text = text.substr(0, wordPos + cursorPos) + (char)inputChar + text.substr(wordPos + cursorPos, text.length());
				changeText(1);
			}
		}

		void TextField::draw(float x, float y)
		{
			m_x = x;
			m_y = y;
			if (Button::clickButton(m_x, m_y, m_w, m_h, (uint8_t)(backColor.r * 255), (uint8_t)(backColor.g * 255), (uint8_t)(backColor.b * 255), (uint8_t)(backColor.a * 255)) && mouseAFSet)
			{
				activeField = this;
			}
			if (text.length() > 0)
			{
				screenText.drawText(text.substr(wordPos, endPos), m_x + 4, m_y + (fontSize * .17), (fontSize * 1.2), (uint8_t)(textColor.r * 255), (uint8_t)(textColor.g * 255), (uint8_t)(textColor.b * 255), (uint8_t)(textColor.a * 255));
			}
			if (activeField == this)
			{
				if (Button::clickButton(m_x, m_y, m_w, m_h))
				{
					mouseSetCursorPos();
				}
				else if (mouseAFSet && (InputManager::getClicked() & MOUSE_LEFT) > 0)
				{
					activeField = nullptr;
				}
				ShapeRenderer::drawRectangle(cursorX + m_x + 2, m_y + (fontSize*.2), 3, fontSize * 1.1, (uint8_t)(textColor.r * 255), (uint8_t)(textColor.g * 255), (uint8_t)(textColor.b * 255), (uint8_t)(textColor.a * 255));
			}
		}

		void TextField::mouseSetCursorPos()
		{
			bool maxedOut = false;
			double shownLength = 0;
			int cursorPosLocal = 0;
			int modifiedMouseX = InputManager::mouseX - (m_x + (m_h*.2));
			if (modifiedMouseX < 0)
			{
				setCursor(0);
			}
			else
			{
				while (shownLength < m_w && shownLength < modifiedMouseX && cursorPosLocal <= endPos)
				{
					shownLength = screenText.getTextWidth(text.substr(wordPos, cursorPosLocal));
					cursorPosLocal++;
				}
				cursorPosLocal--;
				setCursor(cursorPosLocal);
			}
		}

		void TextField::moveCursor(int change)
		{
			if (change < 0)
			{
				for (int i = 0; i < abs(change); i++)
				{
					if (cursorPos > 0)
					{
						cursorPos--;
					}
					else
					{
						if (wordPos > 0)
						{
							wordPos--;
						}
					}
				}
			}
			else
			{
				for (int i = 0; i < change; i++)
				{
					if (wordPos + cursorPos < text.length() && screenText.getTextWidth((text.substr(wordPos, cursorPos + 2))) < m_w - 25)
					{
						cursorPos++;
					}
					else
					{
						if (wordPos + cursorPos < text.length())
						{
							wordPos++;
						}
					}
					if (screenText.getTextWidth(text.substr(wordPos, cursorPos + 1)) > m_w - 15)
					{
						cursorPos--;
						wordPos++;
					}
				}
			}
			updateCursorX();
			setEndPos();
		}

		void TextField::setCursor(int pos)
		{
			if (cursorPos < 0)
			{
				cursorPos = 0;
			}
			if (wordPos + pos <= text.length())
			{
				cursorPos = pos;
			}
			else
			{
				cursorPos = text.length() - wordPos;
			}
			updateCursorX();
		}

		void TextField::changeText(int change)
		{
			if (change < 0)
			{
				for (int i = 0; i < abs(change); i++)
				{
					if (wordPos == 0)
					{
						if (cursorPos > 0)
						{
							cursorPos--;
						}
					}
					else
					{
						wordPos--;
					}
				}
			}
			else
			{
				for (int i = 0; i < change; i++)
				{
					if (screenText.getTextWidth(text.substr(wordPos, cursorPos + 1)) < m_w - 25)
					{
						cursorPos++;
					}
					else
					{
						wordPos++;
					}
					if (screenText.getTextWidth(text.substr(wordPos, cursorPos + 1)) > m_w - 15)
					{
						cursorPos--;
						wordPos++;
					}
				}
			}
			setEndPos();
			updateCursorX();
		}

		void TextField::updateCursorX()
		{
			std::string subWord = text.substr(wordPos, cursorPos);
			cursorX = screenText.getTextWidth(subWord);
		}

		void TextField::setEndPos()
		{
			int i = 0;
			while (i < text.length() && screenText.getTextWidth(text.substr(wordPos, i)) <= m_w - 15)
			{
				i++;
			}
			endPos = i;
		}

		TextField::~TextField()
		{
		}
	}
}
