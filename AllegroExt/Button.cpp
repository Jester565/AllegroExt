#include "Button.h"
#include "InputManager.h"
using namespace AllegroExt::Input;
using namespace AllegroExt::Graphics;

namespace AllegroExt
{
	namespace Input
	{
		Button::Button()
		{
			pressed = false;
		}

		bool Button::overButton(float x, float y, float w, float h)
		{
			return (InputManager::mouseX > x && InputManager::mouseX < x + w && InputManager::mouseY > y && InputManager::mouseY < y + h);
		}

		bool Button::clickButton(float x, float y, float w, float h)
		{
			return (overButton(x, y, w, h) && (InputManager::getClicked() & MOUSE_LEFT) > 0);
		}

		bool Button::clickButton(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		{
			if (overButton(x, y, w, h))
			{
				ShapeRenderer::drawRectangle(x, y, w, h, r / 2, g / 2, b / 2, a);
				return clickButton(x, y, w, h);
			}
			ShapeRenderer::drawRectangle(x, y, w, h, r, g, b, a);
			return false;
		}


		bool Button::clickButton(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t a2)
		{
			if (overButton(x, y, w, h))
			{
				ShapeRenderer::drawRectangle(x, y, w, h, r2, g2, b2, a2);
				return clickButton(x, y, w, h);
			}
			ShapeRenderer::drawRectangle(x, y, w, h, r, g, b, a);
			return false;
		}

		bool Button::pressedButton(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		{
			if (clickButton(x, y, w, h, r, g, b, a))
				pressed = !pressed;
			return pressed;
		}

		bool Button::pressedButton(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t a2)
		{
			if (clickButton(x, y, w, h, r, g, b, a, r2, b2, g2, a2))
				pressed = !pressed;
			return pressed;
		}

		Button::~Button()
		{
		}
	}
}
