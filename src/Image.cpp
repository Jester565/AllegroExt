#include "Image.h"
#include "DisplayManager.h"
#include <cmath>
#ifdef _WIN32
#include <allegro5\allegro.h>
#endif
#define _USE_MATH_DEFINES
#include <math.h>

namespace AllegroExt
{
	namespace Graphics
	{
		std::string Image::PrePath = "";

		Image::Image()
			:imgMap(nullptr), imgFlags(NULL), m_sX(1), m_sY(1), m_cX(0), m_cY(0), m_degs(0), bitmapW(0), bitmapH(0)
		{
			
		}

		Image::Image(const std::string& path)
			:Image()
		{
			set(path);
		}

		Image::Image(const std::string& path, int pW, int pH)
			:Image()
		{
			set(path, pW, pH);
		}

		void Image::set(const std::string& path)
		{
			imgMap = al_load_bitmap((PrePath + path).c_str());
			bitmapW = al_get_bitmap_width(imgMap);
			bitmapH = al_get_bitmap_height(imgMap);
		}

		void Image::set(const std::string& path, int pW, int pH)
		{
			ALLEGRO_BITMAP* oriImgMap = al_load_bitmap((PrePath + path).c_str());
			imgMap = al_create_bitmap(pW, pH);
			ALLEGRO_BITMAP* prevBitmap = al_get_target_bitmap();
			al_set_target_bitmap(imgMap);
			al_draw_scaled_bitmap(oriImgMap, 0, 0, al_get_bitmap_width(oriImgMap), al_get_bitmap_height(oriImgMap), 0, 0, pW, pH, imgFlags);
			al_set_target_bitmap(prevBitmap);
			al_destroy_bitmap(oriImgMap);
			bitmapW = pW;
			bitmapH = pH;
		}

		void Image::draw(float x, float y)
		{
			m_x = x;
			m_y = y;
			if ((m_sX != 1 || m_sY != 1) && (m_degs != 0 || m_cX != 0 || m_cY != 0))
			{
				al_draw_scaled_rotated_bitmap(imgMap, m_cX, m_cY, x, y,
					m_sX, m_sY, m_degs * (M_PI / 180.0), imgFlags);
			}
			else if (m_sX != 1 || m_sY != 1)
			{
				al_draw_scaled_bitmap(imgMap, 0, 0, bitmapW, bitmapH, x, y, m_sX * bitmapW, m_sY * bitmapH, imgFlags);
			}
			else if (m_degs != 0 || m_cX != 0 || m_cY != 0)
			{
				al_draw_rotated_bitmap(imgMap, m_cX, m_cY, x, y, m_degs * (M_PI / 180.0), imgFlags);
			}
			else
			{
				al_draw_bitmap(imgMap, x, y, imgFlags);
			}
		}

		void Image::draw(float x, float y, float w, float h)
		{
			m_sX = w / bitmapW;
			m_sY = h / bitmapH;
			draw(x, y);
		}

		void Image::setDegs(float degs)
		{
			m_degs = degs;
		}

		void Image::changeDegs(float degs)
		{
			m_degs += degs;
		}

		void Image::setRads(float rads)
		{
			m_degs = rads * (180 / 3.141592653589);
		}

		void Image::changeRads(float rads)
		{
			m_degs += rads * (180 / 3.141592653589);
		}

		void Image::setImageOrigin(float x, float y)
		{
			m_cX = x;
			m_cY = y;
		}

		void Image::setImageOriginScaled(float xS, float yS)
		{
			m_cX = xS * bitmapW;
			m_cY = yS * bitmapH;
		}

		void Image::setFlips(bool xFlip, bool yFlip)
		{
			imgFlags = 0;
			if (xFlip)
				imgFlags |= ALLEGRO_FLIP_HORIZONTAL;
			if (yFlip)
				imgFlags |= ALLEGRO_FLIP_VERTICAL;
		}


		void Image::SetPrePath(const std::string & path)
		{
			PrePath = path;
		}

		Image::~Image()
		{
			if (imgMap != nullptr)
			{
				al_destroy_bitmap(imgMap);
				imgMap = nullptr;
			}
		}
	}
}
