#pragma once
#include "ShapeRenderer.h"

namespace AllegroExt
{
	namespace Input
	{
		class Button
		{
		public:
			Button();

			static bool overButton(float x, float y, float w, float h);

			static bool clickButton(float x, float y, float w, float h);

			static bool clickButton(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a = UINT8_MAX);

			static bool clickButton(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t a2 = UINT8_MAX);

			bool pressedButton(float x, float y, float w, float h, uint8_t, uint8_t g, uint8_t b, uint8_t a = UINT8_MAX);

			bool pressedButton(float x, float y, float w, float h, uint8_t, uint8_t g, uint8_t b, uint8_t a, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t a2 = UINT8_MAX);

			~Button();
		private:
			bool pressed;
		};
	}
}
