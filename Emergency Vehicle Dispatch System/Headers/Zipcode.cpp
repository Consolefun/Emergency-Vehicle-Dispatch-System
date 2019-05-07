#include "Zipcode.h"

Zipcode::Zipcode()
{
	zipcode = 0;
	min_distance = INFINITY;
	visited = false;
}

void Zipcode::addAdjacentEdge(Edge new_edge)
{
	adjacents.push_back(new_edge);
}

void Zipcode::addVehicle(EmergencyVehicle new_vehicle)
{
	vehicles.push_back(new_vehicle);
}
