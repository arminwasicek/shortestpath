//============================================================================
// Name        : astar.cpp
// Author      : Armin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include "points.hpp"
#include "shortestpath.hpp"

using namespace std;






int main() {

	Grid grid(10,5);

	cout << "Hello World" << endl;
	cout << "\033[1;31mbold red text\033[0m\n";

	ShortestPath bfs(&grid);
	//bfs.depthfirst(XYPoint(2,3), XYPoint(3,9));
	bfs.breadthfirst(XYPoint(2,3), XYPoint(3,9));

	XYPoint p(3,3);
	p.neighbours(grid);

	grid.plot();

	return 0;
}
