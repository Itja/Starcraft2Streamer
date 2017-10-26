#pragma once

#include "sc2api/sc2_api.h"

class Streamer {
public:
	Streamer();
	void run(int argc, char ** argv);
private:
	sc2::Coordinator *coordinator;
};