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
	bfs.breadthfirst(XYPoint(2,3), XYPoint(9,3));
}

void run_bfs_w_early_exit()  {
	Grid grid(10,5);
	ShortestPath bfs(&grid);
	auto path = bfs.bfs_with_early_exit(XYPoint(2,3), XYPoint(9,3));
	cout << "GOAL!! ";
	for(auto p : path)  {
		cout << p << ' ';
	}
	cout << endl;
}



int main() {

	cout << "Hello World" << endl;
	cout << "\033[1;31mbold red text\033[0m\n";

	run_bfs_w_early_exit();

//	Grid grid(10,5);
//	ShortestPath bfs(&grid);
//	map<const XYPoint, XYPoint> m;
//
//	m.insert({XYPoint(1,1), XYPoint(2,1) });
//	m.insert({XYPoint(1,2), XYPoint(2,2) });
//	m.insert({XYPoint(1,1), XYPoint(2,3) });
//
//	bfs.printmap(m);




	return 0;
}
