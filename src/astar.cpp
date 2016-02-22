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



void run_dfs()  {
	Grid grid(10,5);
	ShortestPath dfs(&grid);
	dfs.depthfirst(XYPoint(2,3), XYPoint(3,9));
}

void run_bfs()  {
	Grid grid(10,5);
	ShortestPath bfs(&grid);
	bfs.breadthfirst(XYPoint(2,3), XYPoint(3,9));
}

void run_bfsp()  {
	Grid grid(10,5);
	ShortestPath bfs(&grid);
	bfs.bfspath(XYPoint(2,3), XYPoint(3,9));
}



int main() {

	cout << "Hello World" << endl;
	cout << "\033[1;31mbold red text\033[0m\n";

	run_bfsp();


	return 0;
}
