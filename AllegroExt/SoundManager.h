#pragma once
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <map>

namespace AllegroExt
{
	namespace Sound
	{
		static const int NEXT_ID = -1;
		class SoundManager
		{
		public:
			SoundManager();
			bool init();
			bool addIDVol(double vol, int id = NEXT_ID);
			double getVol(int id);
			void removeIDVol(int id);
			bool setIDVol(int id, double vol);
			~SoundManager();

		private:
			std::map<int, double> idVols;
		};
	}
}

