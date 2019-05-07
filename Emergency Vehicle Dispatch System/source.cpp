#include <iostream>
#include "./Headers/Graph.h"
#include "./Headers/Request.h"

using namespace std;

int findZipcodeIdx(Graph g, int zip);
void readInRequests(vector<Request>& requests, ifstream& in);

int main()
{
	// open I/O streams
	ifstream vehicle_data("emergency_vehicles.txt");
	ifstream distance_data("distances.txt");
	ifstream request_data("requests.txt");

	// validate that the input file was opened correctly
	if (!vehicle_data || !distance_data || !request_data)
	{
		cerr << "There was an error attemping to open one of the text files." << endl;
		system("pause");
		exit(1);
	}

	Graph graph;
	vector<Request> requests;
	graph.populateGraph(vehicle_data);
	graph.addEdges(distance_data);
	readInRequests(requests, request_data);

	/*for (int i = 0; i < graph.getGraph().size(); i++)
	{
		for (int j = 0; j < graph.getGraph()[i].getVehicles().size(); j++)
		{
			cout << graph.getGraph()[i].getVehicles()[j].id << " " << graph.getGraph()[i].getVehicles()[j].type << " " << graph.getGraph()[i].getZipcode() << endl;
		}
	}*/

	/*for (int i = 0; i < graph.getGraph().size(); i++)
	{
		for (int j = 0; j < graph.getGraph()[i].getAdjacents().size(); j++)
		{
			cout << graph.getGraph()[graph.getGraph()[i].getAdjacents()[j].target_idx].getZipcode() << " " << graph.getGraph()[i].getAdjacents()[j].distance <<  endl;
		}
	}*/

	/*for (int i = 0; i < requests.size(); i++)
	{
		cout << requests[i].id << " " << requests[i].type << " " << requests[i].zipcode << " " << requests[i].vehicle_id << endl;
	}*/

	/*graph.dijkstras(0);
	vector<Zipcode> shortest_paths = graph.getGraph();

	for (int i = 0; i < shortest_paths.size(); i++)
	{
		cout << "Shortest path from " << graph.getGraph()[0].getZipcode() << " to " << shortest_paths[i].getZipcode() << " is " << shortest_paths[i].getDistance() << endl;
	}
	cout << endl;*/

	for (int i = 0; i < requests.size(); i++)
	{
		int idx_of_zip = findZipcodeIdx(graph, requests[i].zipcode);
		if (idx_of_zip != -1)
		{
			graph.dijkstras(idx_of_zip);
			vector<Zipcode> shortest_paths = graph.getGraph();

			for (int i = 0; i < shortest_paths.size(); i++)
			{
				cout << "Shortest path from " << graph.getGraph()[idx_of_zip].getZipcode() << " to " << shortest_paths[i].getZipcode() << " is " << shortest_paths[i].getDistance() << endl;
			}
			cout << endl;

			graph.resetGraph();
		}
	}

	// close all I/O streams
	vehicle_data.close();
	distance_data.close();
	request_data.close();

	system("pause");
	return 0;
}

int findZipcodeIdx(Graph g, int zip)
{
	vector<Zipcode> zipcodes = g.getGraph();
	for (int i = 0; i < zipcodes.size(); i++)
	{
		if (zipcodes[i].getZipcode() == zip)
		{
			return i;
		}
	}
	return -1;
}

void readInRequests(vector<Request>& requests, ifstream& in)
{
	int request_id = 0;
	int vehicle_type = 0;
	int zip = 0;
	int vehicle_id = 0;

	while (in >> request_id >> vehicle_type >> zip >> vehicle_id)
	{
		Request new_request(request_id, vehicle_type, zip, vehicle_id);
		requests.push_back(new_request);
	}
}


