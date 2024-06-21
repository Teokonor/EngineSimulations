#include "EngineTests.h"

const double doubleIsNullPermissibleError = 0.00000001;

double heatingTest(Engine& engine, const double momentDurationInSeconds) {
	const double overheatingTemperature = engine.getInfo().overheatingTemperature;
	engine.start();
	EngineInfo info = engine.getInfo();
	double time = 0, prevTemperature = info.engineTemperature;
	while (info.engineTemperature < overheatingTemperature) {
		engine.workOneMoment(momentDurationInSeconds);
		time += momentDurationInSeconds;
		info = engine.getInfo();
		if (info.engineTemperature <= prevTemperature) {
			time = INFINITY;
			break;
		}
		prevTemperature = info.engineTemperature;
	}
	return time;
}

std::pair<double, double> powerTest(Engine& engine, const double momentDurationInSeconds) {
	engine.start();
	engine.workOneMoment(momentDurationInSeconds);
	EngineInfo info = engine.getInfo();
	double maxOutput = info.engineOutput, speedWhenOutputIsMax = info.crankshaftSpeed,
		sign = info.crankshaftSpeed > 0 ? 1 : -1;
	while (info.crankshaftBoost * sign > doubleIsNullPermissibleError) {
		engine.workOneMoment(momentDurationInSeconds);
		info = engine.getInfo();
		if (info.engineOutput > maxOutput) {
			maxOutput = info.engineOutput;
			speedWhenOutputIsMax = info.crankshaftSpeed;
		}
	}
	return { maxOutput, speedWhenOutputIsMax };
}

void run_tests(std::ostream& output, Engine& engine, const double momentDurationInSeconds) {
	output << "\nHEATING TEST\nWorking time: " << heatingTest(engine, momentDurationInSeconds) << "\n";
	std::pair<double, double> powerTestResult = powerTest(engine, momentDurationInSeconds);
	output << "\nPOWER TEST\nMax output: " << powerTestResult.first << ", Crunkshaft's speed: " << powerTestResult.second << "\n";
}
