#include <iostream>
#include "./Headers/Graph.h"

using namespace std;

int main()
{
	// open I/O streams
	ifstream vehicle_data("emergency_vehicles.txt");
	ifstream distance_data("distances.txt");
	ifstream request_data("requests.txt");

	// validate that the input file was opened correctly
	if (!vehicle_data || !distance_data || !request_data)
	{
		cerr << "There was an error while attemping to open one of the text files." << endl;
		system("pause");
		exit(1);
	}

	Graph graph;
	graph.populateGraph(vehicle_data);
	graph.addEdges(distance_data);

	/*for (int i = 0; i < graph.getGraph().size(); i++)
	{
		for (int j = 0; j < graph.getGraph()[i].getVehicles().size(); j++)
		{
			cout << graph.getGraph()[i].getVehicles()[j].id << " " << graph.getGraph()[i].getVehicles()[j].type << " " << graph.getGraph()[i].getZipcode() << endl;
		}
	}*/

	for (int i = 0; i < graph.getGraph().size(); i++)
	{
		for (int j = 0; j < graph.getGraph()[i].getAdjacents().size(); j++)
		{
			cout << graph.getGraph()[i].getAdjacents()[j].target << " " << graph.getGraph()[i].getAdjacents()[j].distance <<  endl;
		}
	}

	

	// close all I/O streams
	vehicle_data.close();
	distance_data.close();
	request_data.close();

	system("pause");
	return 0;
}
