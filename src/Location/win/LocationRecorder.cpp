#include "LocationRecorder.h"
#include "../../Application/Hargoile.h"
#include "../../Application/MovementSimulator.h"

void LocationRecorder::start() throw(Exception)
{
	Route genRoute;
	genRoute = simulateMovement("auto gen", 1, 200, 2.78);
	std::for_each(genRoute.getGeoPointData().begin(), genRoute.getGeoPointData().end(),
		[&](GeoPoint g) -> void {
			Hargoile::getInstance().addNewPosition(g);
	} );
}