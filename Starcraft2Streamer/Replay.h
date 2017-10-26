#pragma once
#include "sc2api/sc2_replay_observer.h"
#include "sc2api/sc2_api.h"

class Replay : public sc2::ReplayObserver {
public:
	std::vector<uint32_t> count_units_built_;

	Replay() : sc2::ReplayObserver() {
	}

	

	void OnGameStart() final;

	void OnUnitCreated(const sc2::Unit* unit) final;

	void OnStep() final;

	void OnGameEnd() final;
};