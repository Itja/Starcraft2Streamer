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

	virtual bool IgnoreReplay(const sc2::ReplayInfo& replay_info, uint32_t& player_id);

private:
	//On "faster" the game runs at 22.4 gameloops per second
	//for each step, ~44642.8571us are optimal for normal observation or even less for "boring" phases
	static const double optimal_elapsed_us;
	static const double offset_us;
	std::chrono::time_point<std::chrono::steady_clock> start_time, last_step_time;
};