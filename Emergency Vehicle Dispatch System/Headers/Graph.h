#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <map>
#include "./Zipcode.h"

class Graph
{
private:
  std::vector<Zipcode> zipcodes;
public:
  //Getters
  std::vector<Zipcode> getGraph() { return zipcodes; };

  //Member functions
  void addZipcode(Zipcode new_zip);
  void addVehicleToZip(EmergencyVehicle vehicle_to_add);
  void populateGraph(std::ifstream& in);
  void addEdges(std::ifstream& in);
  int getMinZipcode(std::vector<Zipcode> z);
  void resetGraph();
  void allocateVehicleAtZip(int idx, int vehicle_id);
  std::multimap<int, Zipcode> dijkstras(int idx);

};

#endif
