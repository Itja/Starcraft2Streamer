// Starcraft2Streamer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Starcraft2Streamer.h"
#include "Replay.h"
#include "sc2utils/sc2_manage_process.h"
#include "logging.h"


int main(int argc, char **argv)
{
	log_info("Starcraft 2 Streamer (built " << __DATE__ << " " << __TIME__ << ") started");
	Streamer strm;
	strm.run(argc, argv);
	log_info("Starcraft 2 Streamer finished.")
}

Streamer::Streamer()
{
}

void Streamer::run(int argc, char **argv)
{
	coordinator = new sc2::Coordinator();
	std::cout << "bar";
	if (!coordinator->LoadSettings(argc, argv)) {
		log_error("sc2::Coordinator LoadSettings failed")
		throw new std::exception("sc2:Coordinator couldn't LoadSettings");
	}


	std::string replay_path = "D:/proj/sc2ai/replays/377ProtossBot-v-CCZergBot-BelShirVestigeLE.SC2Map.SC2Replay";
	//the C++ Lib takes either a path including one or more replays or a single file ending in ".SC2Replay" (capitalization probably needed) 

	log_info("coordinator->LoadSettings() successful, loading replay(s) from " << replay_path);

	//TODO: coordinator->SetRealtime(true); //does not work because of https://github.com/Blizzard/s2client-api/blob/master/src/sc2api/sc2_coordinator.cc#L690 ?
	coordinator->SetProcessPath("D:/games/StarCraft II/Versions/Base57507/SC2_x64.exe"); //NEEDED when using SetDataVersion which saves whole seconds on startup
	//TODO: we always need the correct exe
	coordinator->SetDataVersion("1659EF34997DA3470FF84A14431E3A86"); //TODO: always have the correct version ready for the replay coming up
	//TODO: data version really necessary if we already set the correct exe version to use?

	//todo: coordinator->SetRender(...)
	//coordinator->SetWindowSize(1920, 1080);
	coordinator->SetWindowSize(700, 300);
	//coordinator->SetWindowLocation(0, 0);
	
	if (!coordinator->SetReplayPath(replay_path)) {
		log_error("Couldn't find replays in " << replay_path)
		throw new std::exception("sc2:Coordinator couldn't find replays");
	}

	Replay replay_obs;

	coordinator->AddReplayObserver(&replay_obs);

	while (coordinator->Update());
	while (!sc2::PollKeyPress());
}
