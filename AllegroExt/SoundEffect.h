#pragma once
#include <allegro5/allegro_audio.h>
#include <string>
#include <list>

class SoundManager;

namespace AllegroExt
{
	namespace Sound
	{
		class SoundManager;

		class SoundEffect
		{
		public:
			SoundEffect(SoundManager* soundManager);
			SoundEffect(SoundManager* soundManager, const std::string& fileName, int volID);
			bool init(const std::string& fileName, int volID);
			ALLEGRO_SAMPLE_ID* play(double vol = 1.0, double pan = 0.0, double speed = 1.0);
			void stop();
			void stop(ALLEGRO_SAMPLE_ID* sampleID);
			~SoundEffect();

		protected:
			ALLEGRO_SAMPLE* sample;
			ALLEGRO_SAMPLE_ID* lastID;
			SoundManager* sm;
			int volID;
		};
	}
}
