#include "InternalCombustionEngine.h"



void InternalCombustionEngine::find_M() {
	auto nextPoint = pointsOfFunction_M_on_V.upper_bound(V_crankshaftSpeed);
	auto prevPoint = nextPoint;
	if (nextPoint == pointsOfFunction_M_on_V.begin()) {
		nextPoint++;
		V_crankshaftSpeed = prevPoint->first;
	}
	else {
		prevPoint--;
	}
	if (nextPoint == pointsOfFunction_M_on_V.end()) {
		V_crankshaftSpeed = prevPoint->first;
		prevPoint--;
		nextPoint--;
	}
	double V0 = prevPoint->first, V1 = nextPoint->first, M0 = prevPoint->second, M1 = nextPoint->second,
		ratio = ((M1 - M0) / (V1 - V0));
	M_torque = M0 + ratio * (V_crankshaftSpeed - V0);
}



void InternalCombustionEngine::start() {
	T_engine = T_envir;
	V_crankshaftSpeed = 0;
	find_M();
	N_engineOutput = M_torque * V_crankshaftSpeed / 1000;

	Vh_heatingSpeed = M_torque * Hm_coeff_Vh_on_M + V_crankshaftSpeed * V_crankshaftSpeed * Hv_coeff_Vh_on_V;
	Vc_coolingSpeed = C_coeff_Vc_on_T * (T_envir - T_engine);
	a_crankshaftBoost = M_torque / I_inertiaMoment;
}



void InternalCombustionEngine::workOneMoment(const double momentDurationInSeconds) {
	double V0 = V_crankshaftSpeed;

	T_engine += (Vh_heatingSpeed + Vc_coolingSpeed) * momentDurationInSeconds;
	V_crankshaftSpeed += a_crankshaftBoost * momentDurationInSeconds;
	find_M();
	N_engineOutput = M_torque * V_crankshaftSpeed / 1000;

	Vh_heatingSpeed = M_torque * Hm_coeff_Vh_on_M + V_crankshaftSpeed * V_crankshaftSpeed * Hv_coeff_Vh_on_V;
	Vc_coolingSpeed = C_coeff_Vc_on_T * (T_envir - T_engine);
	a_crankshaftBoost = M_torque / I_inertiaMoment;
}
