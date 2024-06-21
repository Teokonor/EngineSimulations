#pragma once
#include "Engine.h"
#include <utility>
#include <ostream>

double heatingTest(Engine& engine, const double momentDurationInSeconds);

// Returning: first is max output, second is crankshaft's speed
std::pair<double, double> powerTest(Engine& engine, const double momentDurationInSeconds);

void run_tests(std::ostream& output, Engine& engine, const double momentDurationInSeconds);
