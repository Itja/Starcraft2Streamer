#include "stdafx.h"
#include "Replay.h"
#include <iostream>
#include "logging.h"

void Replay::OnGameStart() {
	log_debug("Replay::OnGameStart called");
	const sc2::ObservationInterface* obs = Observation();
	assert(obs->GetUnitTypeData().size() > 0);
	count_units_built_.resize(obs->GetUnitTypeData().size());
	std::fill(count_units_built_.begin(), count_units_built_.end(), 0);
}

void Replay::OnUnitCreated(const sc2::Unit * unit){
	log_debug("Replay::OnUnitCreated called");
	assert(uint32_t(unit->unit_type) < count_units_built_.size());
	++count_units_built_[unit->unit_type];
}

void Replay::OnStep()
{
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
