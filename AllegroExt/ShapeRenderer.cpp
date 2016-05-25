#include "ShapeRenderer.h"
#include "Core.h"
#include <stdio.h>
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#define _USE_MATH_DEFINES
#include <cmath>

namespace AllegroExt
{
	namespace Graphics
	{
		float ShapeRenderer::xOff = 0;
		float ShapeRenderer::yOff = 0;
		float ShapeRenderer::xScale = 1;
		float ShapeRenderer::yScale = 1;
		float ShapeRenderer::wScale = 1;
		float ShapeRenderer::hScale = 1;
		void ShapeRenderer::drawLine(float x1, float y1, float x2, float y2, float lineW, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		{
			ALLEGRO_COLOR color;
			if (a != UINT8_MAX)
				color = al_map_rgba(r, g, b, a);
			else
				color = al_map_rgb(r, g, b);
			al_draw_line((x1 + xOff) * xScale, (y1 + yOff) * yScale, (x2 + xOff) * xScale, (y2 + yOff) * yScale, color, lineW);
		}

		void ShapeRenderer::drawRectangle(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		{
			ALLEGRO_COLOR color;
			if (a != UINT8_MAX)
				color = al_map_rgba(r, g, b, a);
			else
				color = al_map_rgb(r, g, b);
			float adjustedX = (x + xOff) * xScale;
			float adjustedY = (y + yOff) * yScale;
			al_draw_filled_rectangle(adjustedX, adjustedY, adjustedX + w * wScale, adjustedY + h * hScale, color);
		}

		void ShapeRenderer::drawCircle(float x, float y, float rad, uint8_t  r, uint8_t g, uint8_t b, uint8_t a)
		{
			ALLEGRO_COLOR color;
			if (a != UINT8_MAX)
				color = al_map_rgba(r, g, b, a);
			else
				color = al_map_rgb(r, g, b);
			float adjustedX = (x + xOff) * xScale;
			float adjustedY = (y + yOff) * yScale;
			al_draw_filled_circle(adjustedX, adjustedY, rad * ((xScale + yScale)/2), color);
		}

		void ShapeRenderer::drawArc(float x, float y, float rad, float iPheta, float dPheta, uint8_t r, uint8_t g, uint8_t b, uint8_t a, float thickness)
		{
			ALLEGRO_COLOR color;
			if (a != UINT8_MAX)
				color = al_map_rgba(r, g, b, a);
			else
				color = al_map_rgb(r, g, b);
			float adjustedX = (x + xOff) * xScale;
			float adjustedY = (y + yOff) * yScale;
			al_draw_arc(adjustedX, adjustedY, rad * ((xScale + yScale) / 2), iPheta, dPheta, color, thickness);
		}
	}
}
