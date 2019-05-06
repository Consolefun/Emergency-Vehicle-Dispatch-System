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
	int vehicle_id = 0;
	int vehicle_type = 0;
	int zip = 0;
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
	int zipcode1 = 0;
	int zipcode2 = 0;
	int distance = 0;
	int previous_zip = 0;
	int idx_of_first_zip = 0;
	int idx_of_next_zip = 0;
	while (in >> zipcode1 >> zipcode2 >> distance)
	{
		idx_of_next_zip = (zipcode2 % 10) + 1;
		if (previous_zip != zipcode1)
		{
			idx_of_first_zip++;
		}

		Edge edge1(zipcode2, distance);
		zipcodes[idx_of_first_zip].addAdjacentEdge(edge1);

		
		Edge edge2(zipcode1, distance);
		zipcodes[idx_of_next_zip].addAdjacentEdge(edge2);

		previous_zip = zipcode1;
	}
}
