#ifndef MOVEMENTSIMULATOR_H
#define MOVEMENTSIMULATOR_H

#include "../Utility/String.h"
#include "Route.h"

Route simulateMovement(String routeName, int updateInterval, int distance, double speed);
// Deprecated
/*
void generate(RouteData &genRoute, String routeName, int nMaxIteration);
*/

#endif // MOVEMENTSIMULATOR_H
