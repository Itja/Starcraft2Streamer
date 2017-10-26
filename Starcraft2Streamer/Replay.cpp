#include "stdafx.h"
#include "Replay.h"
#include <iostream>
#include "logging.h"
#include <thread>
#include <chrono>

const double Replay::optimal_elapsed_ms = 44.6429;

void Replay::OnGameStart() {
	log_debug("Replay::OnGameStart called");
	const sc2::ObservationInterface* obs = Observation();
	assert(obs->GetUnitTypeData().size() > 0);
	count_units_built_.resize(obs->GetUnitTypeData().size());
	std::fill(count_units_built_.begin(), count_units_built_.end(), 0);
	start_time = std::chrono::high_resolution_clock::now();
	last_step_time = start_time;
}

void Replay::OnUnitCreated(const sc2::Unit * unit){
	assert(uint32_t(unit->unit_type) < count_units_built_.size());
	++count_units_built_[unit->unit_type];
}

void Replay::OnStep()
{
	//Currently, real time mode is not possible. Thus, we try to emulate it here using sleeping.

	auto current_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_dur = current_time - last_step_time;
	auto elapsed = elapsed_dur.count();
	double to_sleep = optimal_elapsed_ms - elapsed;
	if (to_sleep > 0) {
		std::this_thread::sleep_for(std::chrono::microseconds((long) (to_sleep * 1000)));
	}
	log_debug("sleep: " << to_sleep << "ms")

	last_step_time = current_time;
}

void Replay::OnGameEnd()
{
	log_debug("Replay::OnGameEnd called");
	std::cout << "Units created:" << std::endl;
	const sc2::ObservationInterface* obs = Observation();
	const sc2::UnitTypes& unit_types = obs->GetUnitTypeData();
	for (uint32_t i = 0; i < count_units_built_.size(); ++i) {
		if (count_units_built_[i] == 0) {
			continue;
		}

		std::cout << unit_types[i].name << ": " << std::to_string(count_units_built_[i]) << std::endl;
	}
	std::cout << "Finished" << std::endl;
}
