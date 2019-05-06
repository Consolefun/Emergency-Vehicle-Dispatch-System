#include "Graph.h"

void Graph::addZipcode(Zipcode new_zip)
{
	zipcodes.push_back(new_zip);
}

void Graph::addVehicleToZip(EmergencyVehicle vehicle_to_add)
{
	zipcodes.back().addVehicle(vehicle_to_add);
}

void Graph::populateGraph(std::ifstream& in)
{
	int vehicle_id, vehicle_type, zip = 0;
	int previous_zip = 0;

	while (in >> vehicle_id >> vehicle_type >> zip)
	{
		EmergencyVehicle new_vehicle(vehicle_id, vehicle_type);
		if (zip != previous_zip)
		{
			Zipcode new_zipcode;
			new_zipcode.setZipcode(zip);
			new_zipcode.addVehicle(new_vehicle);
			addZipcode(new_zipcode);

			previous_zip = zip;
		}
		else
		{
			addVehicleToZip(new_vehicle);
		}
	}
}

void Graph::addEdges(std::ifstream& in)
{
	int zipcode1, zipcode2, distance = 0;
	int cnt = 0;
	while (in >> zipcode1 >> zipcode2 >> distance)
	{
		Edge edge1(zipcode2, distance);
		zipcodes[cnt].addAdjacentEdge(edge1);
			
		if (cnt != zipcodes.size() - 1)
		{
			Edge edge2(zipcode1, distance);
			zipcodes[cnt + 1].addAdjacentEdge(edge2);
		}
		cnt++;
	}
}