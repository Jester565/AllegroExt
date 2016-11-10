#pragma once
#include "ScreenText.h"

namespace AllegroExt
{
	namespace Graphics
	{
		class MLScreenText : public ScreenText
		{
		public:
			MLScreenText();

			virtual void drawText(const std::string& str, float x, float y, float fontSize, uint8_t = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = UINT8_MAX) override;

			virtual void drawCenteredText(const std::string& str, float x, float y, float fontSize, uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = UINT8_MAX) override;
			
			void setMaxWidth(int mw)
			{
				maxWidth = mw;
			}

			void setLHScale(float lhScale)
			{
				this->lhScale = lhScale;
			}

			float getTextHeight(const std::string& str, float w, float fontSize);

			~MLScreenText();

		private:
			int maxWidth;
			float lhScale;
		};
	}
}