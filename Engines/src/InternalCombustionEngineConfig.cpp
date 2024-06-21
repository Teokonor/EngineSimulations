#include "InternalCombustionEngineConfig.h"
#include <sstream>

const double doubleIsNullPermissibleError = 0.00000001;

bool equal(double a, double b) {
	if (a - b >= -doubleIsNullPermissibleError && a - b <= doubleIsNullPermissibleError) {
		return true;
	}
	return false;
}

InternalCombustionEngineConfig::InternalCombustionEngineConfig(std::istream& input) {
	input >> inertiaMoment;
	std::string line;
	std::getline(input, line);
	std::getline(input, line);
	std::istringstream lineStr(line);
	double V, M;
	while (!lineStr.eof()) {
		lineStr >> V >> M;
		if (isnan(V) || isnan(M)) {
			break;
		}
		pointsOfFunction_torque_on_crankshaftSpeed.insert({ V, M });
	}
	input >> overheatingTemperature >> coeff_heatingSpeed_on_torque >> coeff_heatingSpeed_on_crankshaftSpeed >> coeff_coolingSpeed_on_temperatures;
}

bool InternalCombustionEngineConfig::configIsCorrect() {
	if (inertiaMoment <= 0 || overheatingTemperature <= -273 || coeff_heatingSpeed_on_crankshaftSpeed < 0 || coeff_coolingSpeed_on_temperatures < 0 ||
		pointsOfFunction_torque_on_crankshaftSpeed.size() < 2 || 
		pointsOfFunction_torque_on_crankshaftSpeed.find(0) == pointsOfFunction_torque_on_crankshaftSpeed.end() ||
		equal(pointsOfFunction_torque_on_crankshaftSpeed.at(0), 0)
		) {
		return false;
	}
	auto edge = pointsOfFunction_torque_on_crankshaftSpeed.begin();
	if (pointsOfFunction_torque_on_crankshaftSpeed.at(0) > 0) {
		edge = pointsOfFunction_torque_on_crankshaftSpeed.end();
		edge--;
	}
	if (!equal(edge->second, 0)) {
		return false;
	}
	return true;
}
