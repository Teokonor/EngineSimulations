#include "InternalCombustionEngine.h"
#include "EngineTests.h"
#include <iostream>
#include <fstream>

const char* configFileName = "config.txt";

int main() {
	std::ifstream configFile(configFileName);
	InternalCombustionEngineConfig conf(configFile);
	if (!conf.configIsCorrect()) {
		std::cout << "Config is incorrect!";
		return -2;
	}
	InternalCombustionEngine ourEngine(conf);
	double envirTemp = 0, momentDur = 0;
	std::cout << "Please, enter the environment temperature in degrees Celsius: ";
	std::cin >> envirTemp;
	ourEngine.initConditions(envirTemp);
	std::cout << "\nPlease, enter the duration of one simulation moment in seconds: ";
	std::cin >> momentDur;
	if (envirTemp <= -273 || momentDur <= 0) {
		std::cout << "\nInput is incorrect!";
		return -3;
	}

	run_tests(std::cout, ourEngine, momentDur);
}
