#include "SoundEffect.h"
#include "SoundManager.h"
#include <allegro5/allegro_acodec.h>
#include <iostream>

namespace AllegroExt
{
	namespace Sound
	{
		SoundEffect::SoundEffect(SoundManager* sm)
			:sm(sm), sample(nullptr), volID(0), lastID(nullptr)
		{
		}

		SoundEffect::SoundEffect(SoundManager * sm, const std::string & fileName, int volID)
			: sm(sm), sample(nullptr), volID(0), lastID(nullptr)
		{
			init(fileName, volID);
		}

		bool SoundEffect::init(const std::string& fileName, int volID)
		{
			sample = al_load_sample(fileName.c_str());
			if (sample != nullptr)
			{
				return true;
			}
			std::cerr << "The file " << fileName << " does not exist and the sound is null" << std::endl;
			return false;
		}

		ALLEGRO_SAMPLE_ID* SoundEffect::play(double vol, double pan, double speed)
		{
			if (sm == nullptr)
			{
				std::cout << "SoundManager is nullptr" << std::endl;
			}
			double idVol = sm->getVol(volID);
			if (idVol == -1)
			{
				idVol = 1.0;
			}
			al_play_sample(sample, vol * idVol, pan, speed, ALLEGRO_PLAYMODE_ONCE, lastID);
			return lastID;
		}

		void SoundEffect::stop()
		{
			if (lastID != nullptr)
			{
				al_stop_sample(lastID);
			}
		}

		void SoundEffect::stop(ALLEGRO_SAMPLE_ID* sampleID)
		{
			al_stop_sample(sampleID);
		}

		SoundEffect::~SoundEffect()
		{
			al_destroy_sample(sample);
			sample = nullptr;
		}
	}
}
