#pragma once
#include "LoadSign.h"
#include <vector>

namespace AllegroExt
{
	namespace Graphics
	{
		namespace Loading
		{
			struct LoadLine
			{
				const int NOT_FINISHED = 0;
				
				const int COVER_FINISH = 1;

				const int ELIMINATE_FINISH = 2;

				LoadLine(float startpos, float iV, float a, int r, int g, int b, int alpha);
				
				void draw();
				
				void draw(float x, float y, float w, float h);

				void setPheta(float& pheta, float& pv);

				void setReceed(bool mode = true)
				{
					receed = mode;
				}

				void coverFinish()
				{
					mode = COVER_FINISH;
				}

				void eliminateFinish()
				{
					mode = ELIMINATE_FINISH;
				}

			protected:
				float a;

				float p;

				float pv;

				float thickness;

				bool receed;

				bool visible;

				int r, g, b, alpha, mode;
			};

			class DefaultLoadSign:public LoadSign
			{
			public:
				DefaultLoadSign(float iV = .6, float a = .1);

				void draw(float x, float y, float w, float h);

				void create();

				void setAsFinished(bool success = true) override;

				bool isFinished()
				{
					return finished;
				}

				~DefaultLoadSign();

			protected:
				
				std::vector <LoadLine> lines;

				float iV;

				float a;

				float alpha;
			};
		}
	}
}
