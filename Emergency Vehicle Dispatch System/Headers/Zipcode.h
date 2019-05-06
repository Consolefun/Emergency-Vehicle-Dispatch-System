#ifndef ZIPCODE_H
#define ZIPCODE_H

#include "./EmergencyVehicle.h"
#include "./Edge.h"
#include <vector>

class Zipcode
{
private:
	int zipcode;
	int previous_zipcode;
	float min_distance;
	bool visited;
	std::vector<Edge> adjacents;
	std::vector<EmergencyVehicle> vehicles;
public:
	//Constructor
	Zipcode();

	// Getters
	int getZipcode() { return zipcode; };
	int getPrevZipcode() { return previous_zipcode; };
	float getDistance() { return min_distance; };
	bool getVisited() { return visited; };
	std::vector<Edge> getAdjacents() { return adjacents; };
	std::vector<EmergencyVehicle> getVehicles() { return vehicles; };

	//Setters
	void setZipcode(int new_zip) { zipcode = new_zip; };
	void setPrevZipcode(int prev_zip) { previous_zipcode = prev_zip; };
	void setDistance(float new_distance) { min_distance = new_distance; };
	void setVisited() { visited = true; };
	
	//Member functions
	void addAdjacentEdge(Edge new_edge);
	void addVehicle(EmergencyVehicle new_vehicle);
};

#endif /* end of include guard: */
