#ifndef EMERGENCYVEHICLE_H
#define EMERGENCYVEHICLE_H

#include <stdbool.h>

struct EmergencyVehicle
{
  int id;
  int type;
  bool available;

  EmergencyVehicle()
  {
	  id = 0;
	  type = 0;
	  available = true;
  }

  EmergencyVehicle(int new_id, int t)
  {
	  id = new_id;
	  type = t;
	  available = true;
  }
};

#endif /* end of include guard: */
