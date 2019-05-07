#include <iostream>
#include "./Headers/Graph.h"
#include "./Headers/Request.h"

using namespace std;

int findZipcodeIdx(Graph g, int zip);
void readInRequests(vector<Request>& requests, ifstream& in);
void processRequests(Graph g, vector<Request> req);

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
	processRequests(graph, requests);

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

void processRequests(Graph g, vector<Request> req)
{
	for (int i = 0; i < req.size(); i++)
	{
		int idx_of_allocation = 0;
		int zip_of_allocation = 0;
		int idx_of_request = findZipcodeIdx(g, req[i].zipcode);
		if (idx_of_request != -1)
		{
			multimap<int, Zipcode> shortest_paths = g.dijkstras(idx_of_request);

			for (auto it = shortest_paths.begin(); it != shortest_paths.end(); ++it) {
				idx_of_allocation = findZipcodeIdx(g, it->second.getZipcode());
				vector<EmergencyVehicle> current_vehicles = g.getGraph()[idx_of_allocation].getVehicles();

				for (int j = 0; j < current_vehicles.size(); j++) {
					if (req[i].type == current_vehicles[j].type && current_vehicles[j].available == true) {
						req[i].fillRequest(current_vehicles[j].id, it->first);
						zip_of_allocation = it->second.getZipcode();
						g.allocateVehicleAtZip(idx_of_allocation, req[i].vehicle_id);
						break;
					}
				}

				if (req[i].vehicle_id != -1)
				{
					break;
				}
			}
			cout << "Vehicle #" << req[i].vehicle_id << " was dispatched from " << zip_of_allocation << " to " << req[i].zipcode << "." << endl;
		}
		g.resetGraph();
	}
}
