#ifndef ZIPCODE_H
#define ZIPCODE_H

#include "./EmergencyVehicle.h"
#include "./Edge.h"
#include <vector>

class Zipcode
{
private:
	int zipcode;
	float min_distance;
	bool visited;
	std::vector<Edge> adjacents;
	std::vector<EmergencyVehicle> vehicles;
public:
	//Constructor
	Zipcode();

	// Getters
	int getZipcode() { return zipcode; };
	float getDistance() { return min_distance; };
	bool isVisited() { return visited; };
	std::vector<Edge> getAdjacents() { return adjacents; };
	std::vector<EmergencyVehicle> getVehicles() { return vehicles; };

	//Setters
	void setZipcode(int new_zip) { zipcode = new_zip; };
	void setDistance(float new_distance) { min_distance = new_distance; };
	void setVisited(bool flag) { visited = flag; };

	//Member functions
	void addAdjacentEdge(Edge new_edge);
	void addVehicle(EmergencyVehicle new_vehicle);
	void allocateVehicle(int id);
};

#endif /* end of include guard: */
