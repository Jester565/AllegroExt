#pragma once

namespace AllegroExt
{
	namespace Graphics
	{
		namespace Loading
		{
			class LoadSign
			{
			public:
				LoadSign();

				virtual void draw(float x, float y, float w, float h);

				virtual void setAsFinished(bool loaded = true)
				{
					finished = true;
					success = loaded;
				}

				~LoadSign();

			protected:
				bool finished;

				bool success;
			};
		}
	}
}

