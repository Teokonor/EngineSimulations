#pragma once

struct EngineInfo {
	double inertiaMoment, overheatingTemperature;
	double engineTemperature, torque, crankshaftSpeed, engineOutput;
	double crankshaftBoost, heatingSpeed, coolingSpeed;
};

class Engine {
public:
	virtual void start() = 0;
	virtual void workOneMoment(const double momentDurationInSeconds) = 0;
	virtual EngineInfo getInfo() const = 0;
};
