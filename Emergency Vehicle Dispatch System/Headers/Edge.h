#ifndef EDGE_H
#define EDGE_H

struct Edge
{
  int target_idx;
  int distance;

  Edge()
  {
	  target_idx = 0;
	  distance = 0;
  }

  Edge(int zip, int weight)
  {
	  target_idx = zip;
	  distance = weight;
  }
};

#endif
