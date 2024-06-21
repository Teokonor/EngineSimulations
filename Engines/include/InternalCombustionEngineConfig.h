#pragma once
#include <map>
#include <istream>

struct InternalCombustionEngineConfig {
	double inertiaMoment = 0, overheatingTemperature = 0;
	double coeff_heatingSpeed_on_torque = 0, coeff_heatingSpeed_on_crankshaftSpeed = 0, coeff_coolingSpeed_on_temperatures = 0;
	std::map<double, double> pointsOfFunction_torque_on_crankshaftSpeed;

	InternalCombustionEngineConfig(std::istream& input);
	bool configIsCorrect();
};
