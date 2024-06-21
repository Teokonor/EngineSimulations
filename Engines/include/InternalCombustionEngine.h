#pragma once
#include "Engine.h"
#include "InternalCombustionEngineConfig.h"
#include <map>

class InternalCombustionEngine final : public Engine {
	const double I_inertiaMoment, T_overheating, Hm_coeff_Vh_on_M, Hv_coeff_Vh_on_V, C_coeff_Vc_on_T;
	std::map<double, double> pointsOfFunction_M_on_V;

	double T_envir = 0;

	double T_engine = 0, M_torque = 0, V_crankshaftSpeed = 0, N_engineOutput = 0;
	double a_crankshaftBoost = 0, Vh_heatingSpeed = 0, Vc_coolingSpeed = 0;

	void find_M();
public:
	InternalCombustionEngine(const InternalCombustionEngineConfig& conf) :

		I_inertiaMoment(conf.inertiaMoment), T_overheating(conf.overheatingTemperature), Hm_coeff_Vh_on_M(conf.coeff_heatingSpeed_on_torque),
		Hv_coeff_Vh_on_V(conf.coeff_heatingSpeed_on_crankshaftSpeed), C_coeff_Vc_on_T(conf.coeff_coolingSpeed_on_temperatures),
		pointsOfFunction_M_on_V(conf.pointsOfFunction_torque_on_crankshaftSpeed) {}

	void initConditions(const double environmentTemperature) { T_envir = environmentTemperature; }
	void start() override;
	void workOneMoment(const double momentDurationInSeconds) override;

	EngineInfo getInfo() const override {
		return{ I_inertiaMoment, T_overheating,
			T_engine, M_torque, V_crankshaftSpeed, N_engineOutput,
			a_crankshaftBoost, Vh_heatingSpeed, Vc_coolingSpeed };
	}
};
