#include "Music.h"
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <iostream>

namespace AllegroExt
{
	namespace Sound
	{
		Music::Music(SoundManager * sm)
			:sm(sm)
		{
		}

		Music::Music(SoundManager* sm, const std::string& fileName)
			:sm(sm)
		{
			init(fileName);
		}

		bool Music::init(const std::string& fileName)
		{
			sample = al_load_sample(fileName.c_str());
			if (sample == nullptr)
			{
				std::cerr << "The file " << fileName << " does not exist and the sound is null" << std::endl;
				return false;
			}
			sampleInstance = al_create_sample_instance(sample);
			al_set_sample_instance_playmode(sampleInstance, ALLEGRO_PLAYMODE_LOOP);
			al_attach_sample_instance_to_mixer(sampleInstance, al_get_default_mixer());
			return true;
		}

		void Music::play()
		{
			al_play_sample_instance(sampleInstance);
		}

		void Music::stop()
		{
			al_stop_sample_instance(sampleInstance);
		}

		Music::~Music()
		{
			al_destroy_sample(sample);
			al_destroy_sample_instance(sampleInstance);
		}
	}
}