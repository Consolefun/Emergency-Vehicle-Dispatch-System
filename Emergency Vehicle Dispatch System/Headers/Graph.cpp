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

	bool first_iteration = true;
	while (in >> zipcode1 >> zipcode2 >> distance)
	{
		if (first_iteration)
		{
			previous_zip = zipcode1;
			first_iteration = false;
		}
		else
		{
			if (previous_zip != zipcode1)
			{
				idx_of_first_zip++;
			}
		}

		idx_of_next_zip = (zipcode2 % 10) + 1;

		Edge edge1(idx_of_next_zip, distance);
		zipcodes[idx_of_first_zip].addAdjacentEdge(edge1);

		Edge edge2(idx_of_first_zip, distance);
		zipcodes[idx_of_next_zip].addAdjacentEdge(edge2);

		//std::cout << zipcodes[idx_of_first_zip].getZipcode() << " is connected to " << zipcodes[idx_of_next_zip].getZipcode() << std::endl;

		previous_zip = zipcode1;
	}
}

int Graph::getMinZipcode(std::vector<Zipcode> z)
{
	Zipcode min;
	int idx = 0;
	for (int i = 0; i < z.size(); i++)
	{
		if (!z[i].isVisited())
		{
			min = z[i];
			idx = i;
			break;
		}
	}

	for (int i = 1; i < z.size(); i++)
	{
		if (z[i].getDistance() < min.getDistance() && !z[i].isVisited())
		{
			min = z[i];
			idx = i;
		}
	}
	return idx;
}

void Graph::resetGraph()
{
	for (int i = 0; i < zipcodes.size(); i++)
	{
		zipcodes[i].setDistance(INFINITY);
		zipcodes[i].setVisited(false);
	}
}

std::multimap<int, Zipcode> Graph::dijkstras(int current_idx)
{
	std::multimap<int, Zipcode> shortest_paths;

	zipcodes[current_idx].setDistance(0);
	while (shortest_paths.size() != zipcodes.size())
	{
		std::vector<Edge> adjacents = zipcodes[current_idx].getAdjacents();

		for (int i = 0; i < adjacents.size(); i++)
		{
			if (zipcodes[current_idx].getDistance() + adjacents[i].distance < zipcodes[adjacents[i].target_idx].getDistance())
			{
				zipcodes[adjacents[i].target_idx].setDistance(zipcodes[current_idx].getDistance() + adjacents[i].distance);
			}
		}
		zipcodes[current_idx].setVisited(true);
		shortest_paths.insert(std::pair<int, Zipcode>(zipcodes[current_idx].getDistance(), zipcodes[current_idx]));
		current_idx = getMinZipcode(zipcodes);
	}
	return shortest_paths;
}
