#pragma once
#include "DisplayManager.h"

namespace AllegroExt
{
	namespace Graphics
	{
		class ShapeRenderer
		{
		public:
			static void drawLine(float x1, float y1, float x2, float y2, float lineW, uint8_t r, uint8_t g, uint8_t b, uint8_t a = UINT8_MAX);

			static void drawRectangle(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a = UINT8_MAX);

			static void drawCircle(float x, float y, float rad, uint8_t  r, uint8_t g, uint8_t b, uint8_t a = UINT8_MAX);

			static void drawArc(float x, float y, float rad, float iPheta, float dPheta, uint8_t r, uint8_t g, uint8_t b, uint8_t a = UINT8_MAX, float thickness = 5);
			
			static float xOff;
			static float yOff;
			static float xScale;
			static float yScale;
			static float wScale;
			static float hScale;
		};
	}
}
