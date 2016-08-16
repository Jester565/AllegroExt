#pragma once
#include <string>

class SoundManager;
class ALLEGRO_SAMPLE;
class ALLEGRO_SAMPLE_INSTANCE;

namespace AllegroExt
{
	namespace Sound
	{
		class SoundManager;

		class Music
		{
		public:
			Music(SoundManager* sm);

			Music(SoundManager* sm, const std::string& fileName);

			bool init(const std::string& fileName);

			void play();

			void stop();

			~Music();
		private:
			SoundManager* sm;
			ALLEGRO_SAMPLE* sample;
			ALLEGRO_SAMPLE_INSTANCE* sampleInstance;
		};
	}
}