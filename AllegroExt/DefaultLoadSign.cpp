#include "DefaultLoadSign.h"
#include "ShapeRenderer.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

using namespace AllegroExt::Graphics;

namespace AllegroExt
{
	namespace Graphics
	{
		namespace Loading
		{
			LoadLine::LoadLine(float startPos, float iV, float a, int r, int g, int b, int alpha)
				:p(0), r(r), g(g), b(b), alpha(alpha), a(a), thickness(10), receed(false), visible(false)
			{
				mode = NOT_FINISHED;
				if (pv <= 180)
					pv = std::sqrt(std::pow(iV, 2) + 2 * a * startPos);
				else
					pv = std::sqrt(std::pow(iV, 2) + 2 * a * (180 - (startPos - 180)));
			}

			void LoadLine::draw(float x, float y, float w, float h)
			{
				if (mode == NOT_FINISHED)
				{
					setPheta(p, pv);
				}
				else if (mode == ELIMINATE_FINISH)
				{
					if (pv > 0)
						pv -= .06;
					else
						pv = 0;
				}
				else
				{
					visible = true;
					if (!receed)
					{
						if (pv * pv * 3 < 360)
						{
							pv += .2;
						}
					}
					else
					{
						if (pv > 0)
						{
							pv -= .23;
						}
					}
					thickness = (pv * pv * 3) / 360 * (w * .97);
				}
				if (visible)
				{
					ShapeRenderer::drawArc(x, y, w - thickness, (p - 90) * (M_PI / 180.0), pv * pv * (M_PI / 180.0) * 3, r, g, b, alpha, thickness);
				}
			}

			void LoadLine::setPheta(float& pheta, float& pv)
			{
				if (pheta >= 357)
				{
					pheta = 0;
					pv = .6;
					visible = true;
				}
				if (pheta <= 180)
					pv += a;
				else
					pv -= a;
				pheta += pv;
			}


			DefaultLoadSign::DefaultLoadSign(float iV, float a)
				:iV(iV), a(a)
			{
				create();
			}

			void DefaultLoadSign::create()
			{
				alpha = 255;
				lines.clear();
				lines.push_back(LoadLine(47, iV, a, 255, 0, 0, 140));
				lines.push_back(LoadLine(120, iV, a, 0, 255, 0, 140));
				lines.push_back(LoadLine(280, iV, a, 0, 0, 255, 140));
			}

			void DefaultLoadSign::draw(float x, float y, float w, float h)
			{
				if (alpha > 0)
				{
					ShapeRenderer::drawCircle(x, y, w + 10, 112, 128, 144, alpha/1.3);
					for (int i = 0; i < lines.size(); i++)
					{
						if (finished)
						{
							alpha -= .5;
						}
						if (alpha < 100)
						{
							lines[i].setReceed();
						}
						lines[i].draw(x, y, w, h);
					}
				}
			}

			void DefaultLoadSign::setAsFinished(bool loaded)
			{
				finished = true;
				success = loaded;
				if (success){
					lines[0].eliminateFinish();
					lines[1].coverFinish();
					lines[2].eliminateFinish();
				}
				else
				{
					lines[0].coverFinish();
					lines[1].eliminateFinish();
					lines[2].eliminateFinish();
				}
			}

			DefaultLoadSign::~DefaultLoadSign()
			{
			}
		}
	}
}
