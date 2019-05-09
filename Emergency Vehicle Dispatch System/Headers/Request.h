#ifndef REQUEST_H
#define REQUEST_H

struct Request
{
  int id;
  int type;
  int zipcode;
  int vehicle_id;
  int distance;

  Request(int new_id, int new_type, int new_zip, int new_vehicle_id)
  {
	  id = new_id;
	  type = new_type;
	  zipcode = new_zip;
	  vehicle_id = new_vehicle_id;
	  distance = 0;
  }

  void fillRequest(int id, int dist)
  {
	  vehicle_id = id;
	  distance = dist;
  }
};

#endif /* end of include guard: */
