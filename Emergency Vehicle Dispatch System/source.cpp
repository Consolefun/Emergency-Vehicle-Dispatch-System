#include <iostream>
#include <iomanip>
#include "./Headers/Graph.h"
#include "./Headers/Request.h"

using namespace std;

int findZipcodeIdx(Graph g, int zip);
void readInRequests(vector<Request>& requests, ifstream& in);
void processRequests(Graph g, vector<Request>& req);
void outputRequests(vector<Request> req);

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

	// Place zipcodes on graph
	graph.populateGraph(vehicle_data);

	// Connect zipcodes together
	graph.addEdges(distance_data);

	readInRequests(requests, request_data);
	processRequests(graph, requests);
	outputRequests(requests);

	// close all I/O streams
	vehicle_data.close();
	distance_data.close();
	request_data.close();

	cin.get();
	return 0;
}

int findZipcodeIdx(Graph g, int zip)
{
	//Find the index of a specific zipcode
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

void processRequests(Graph g, vector<Request>& req)
{
	for (int i = 0; i < req.size(); i++)
	{
		// Index of the zipcode the vehicle is coming from
		int idx_of_allocation = 0;

		int idx_of_request = findZipcodeIdx(g, req[i].zipcode);
		if (idx_of_request != -1)
		{
			multimap<int, Zipcode> shortest_paths = g.dijkstras(idx_of_request);

			// Search through shortest paths and check if a matching vehicle is available. If so, allocate it.
			for (auto it = shortest_paths.begin(); it != shortest_paths.end(); ++it) {
				idx_of_allocation = findZipcodeIdx(g, it->second.getZipcode());
				vector<EmergencyVehicle> current_vehicles = g.getGraph()[idx_of_allocation].getVehicles();

				for (int j = 0; j < current_vehicles.size(); j++) {
					if (req[i].type == current_vehicles[j].type && current_vehicles[j].available == true) {
						req[i].fillRequest(current_vehicles[j].id, it->first);
						g.allocateVehicleAtZip(idx_of_allocation, req[i].vehicle_id);
						break;
					}
				}

				// If a vehicle has been allocated, move on to the next request
				if (req[i].vehicle_id != -1)
				{
					break;
				}
			}
		}
		g.resetGraph();
	}
}

void outputRequests(vector<Request> req)
{
	//Do not output unfulfilled requests in table
	vector<Request> invalid_requests;

	// Print column headers
	cout << setw(8) << left << "ID" << setw(13) << left << "VehicleType" << setw(13) << "ZipCode"
		 << setw(11) << left << "VehicleID" << setw(10) << left << "Distance" << endl;

	for (int i = 0; i < req.size(); i++)
	{
		if (req[i].vehicle_id != -1)
		{
			cout << left << setw(8) << req[i].id
				<< left << setw(13) << req[i].type
				<< left << setw(13) << req[i].zipcode
				<< left << setw(11) << req[i].vehicle_id
				<< left << setw(10) << req[i].distance << endl;
		}
		else invalid_requests.push_back(req[i]);
	}

	cout << endl;
	for (int i = 0; i < invalid_requests.size(); i++)
	{
		cout << "The request for zipcode " << invalid_requests[i].zipcode << " was not fulfilled because it is not in the area." << endl;
	}
}
