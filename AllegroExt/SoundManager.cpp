#include "SoundManager.h"
#include <iostream>

namespace AllegroExt
{
	namespace Sound
	{
		SoundManager::SoundManager()
		{
		}

		bool SoundManager::init()
		{
			bool failure = false;
			failure |= !al_init_acodec_addon();
			failure |= !al_install_audio();
			failure |= !al_reserve_samples(1);
			return al_init_acodec_addon();
		}

		bool SoundManager::addIDVol(double vol, int id)
		{
			if (id = NEXT_ID)
			{
				int maxID = -1;
				for (auto iter = idVols.begin(); iter != idVols.end(); iter++)
				{
					if (iter->first > maxID)
					{
						maxID = iter->first;
					}
				}
				id = maxID + 1;
			}
			if (idVols.find(id) != idVols.end())
			{
				std::cerr << "The ID: " << id << " already exists in the idVol map. Creation cancelled..." << std::endl;
				return false;
			}
			idVols.emplace(id, vol);
			return true;
		}

		double SoundManager::getVol(int id)
		{
			double vol = -1;
			auto iter = idVols.find(id);
			if (iter != idVols.end())
			{
				vol = iter->second;
			}
			else
			{
				std::cerr << "Could not find the volID: " << id << " when trying to get a volume..." << std::endl;
			}
			return vol;
		}

		void SoundManager::removeIDVol(int id)
		{
			auto iter = idVols.find(id);
			if (iter != idVols.end())
			{
				idVols.erase(iter);
			}
			else
			{
				std::cerr << "Could not find the volID: " << id << " when trying to erase a volume..." << std::endl;
			}
		}

		bool SoundManager::setIDVol(int id, double vol)
		{
			auto iter = idVols.find(id);
			if (iter != idVols.end())
			{
				iter->second = vol;
			}
			else
			{
				std::cerr << "Could not find volID: " << id << " when setting volume..." << std::endl;
				return false;
			}
			return true;
		}

		SoundManager::~SoundManager()
		{

		}
	}
}
