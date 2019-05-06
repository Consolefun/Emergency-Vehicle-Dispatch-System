#ifndef EDGE_H
#define EDGE_H

struct Edge
{
  int target;
  int distance;

  Edge()
  {
	  target, distance = 0;
  }

  Edge(int zip, int weight)
  {
	  target = zip;
	  distance = weight;
  }
};

#endif
