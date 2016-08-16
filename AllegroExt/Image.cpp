#include "Image.h"
#include "DisplayManager.h"
#include <cmath>
#ifdef _WIN32
#include <allegro5\allegro.h>
#endif

namespace AllegroExt
{
	namespace Graphics
	{
		const std::string Image::prePath = "C:\\Users\\ajcra\\Desktop\\wdir\\woc\\";

		Image::Image()
			:imgMap(nullptr)
		{
			imgMap = nullptr;
			imgFlags = 0;
			m_sX = 1;
			m_sY = 1;
			m_cX = 0;
			m_cY = 0;
			m_degs = 0;
			bitmapW = 0;
			bitmapH = 0;
		}

		Image::Image(std::string path)
			:imgMap(nullptr)
		{
			Image();
			set(path);
		}

		void Image::set(std::string path)
		{
			imgMap = al_load_bitmap((prePath + path).c_str());
			bitmapW = al_get_bitmap_width(imgMap);
			bitmapH = al_get_bitmap_height(imgMap);
		}

		void Image::draw(float x, float y)
		{
			m_x = x;
			m_y = y;
			al_draw_scaled_rotated_bitmap(imgMap, m_cX, m_cY, x, y,
				m_sX, m_sY, m_degs * (3.1415 / 180.0), imgFlags);
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
