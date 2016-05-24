#pragma once
#include <string>
class ALLEGRO_BITMAP;

namespace AllegroExt
{
	namespace Graphics
	{
		class Image
		{
		public:
			Image();
			Image(std::string path);
			void set(std::string path);
			void draw(float x, float y);
			void draw(float x, float y, float w, float h);
			void setDegs(float degs);
			void changeDegs(float degs);
			void setRads(float rads);
			void changeRads(float rads);
			void setImageOrigin(float cX, float cY);
			void setImageOriginScaled(float xS, float yS);
			void setFlips(bool xFlip, bool yFlip);
			~Image();
		private:
			float m_x;
			float m_y;
			float m_sX;
			float m_sY;
			float m_cX;
			float m_cY;
			float m_degs;
			int imgFlags;
			float bitmapW;
			float bitmapH;
			ALLEGRO_BITMAP* imgMap;
			static const std::string prePath;
		};
	}
}
