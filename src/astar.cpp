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
#include "screen.hpp"

using namespace std;

enum algo {
	DIJKSTRA = 0,
	GREEDY,
	ASTAR
};


void run_bfs_w_early_exit()  {
	Grid grid(10,5);
	ShortestPath bfs(&grid);
	auto path = bfs.bfs_with_early_exit(Point2D(2,3), Point2D(9,3));
	cout << "GOAL!! ";
	for(auto p : path)  {
		cout << p << ' ';
	}
	cout << endl;
}

vector<Point2D> run_dijkstra() {
	Grid grid(10,5);
	ShortestPath bfs(&grid);

	grid.setWeight(4,1,1);
	grid.setWeight(4,2,1);
	grid.setWeight(4,3,1);
	grid.setWeight(5,1,2);
	grid.setWeight(5,2,2);
	grid.setWeight(5,3,2);
	grid.setWeight(6,1,1);
	grid.setWeight(6,2,1);
	grid.setWeight(6,3,1);

	return bfs.bfs_dijkstra(Point2D(2,3), Point2D(9,3));
}

vector<Point2D> run_greedy() {
	Grid grid(10,5);
	ShortestPath bfs(&grid);

	grid.setWeight(4,1,3);
	grid.setWeight(4,2,3);
	grid.setWeight(4,3,3);
	grid.setWeight(5,1,9);
	grid.setWeight(5,2,9);
	grid.setWeight(5,3,9);
	grid.setWeight(6,1,3);
	grid.setWeight(6,2,3);
	grid.setWeight(6,3,3);

	return bfs.bfs_greedy(Point2D(2,3), Point2D(9,3));
}

vector<Point2D> run_astar() {
	Grid grid(10,5);
	ShortestPath bfs(&grid);

	grid.setWeight(4,1,3);
	grid.setWeight(4,2,3);
	grid.setWeight(4,3,3);
	grid.setWeight(5,1,9);
	grid.setWeight(5,2,9);
	grid.setWeight(5,3,9);
	grid.setWeight(6,1,3);
	grid.setWeight(6,2,3);
	grid.setWeight(6,3,3);

	return bfs.bfs_astar(Point2D(2,3), Point2D(9,3));
}

int main(int argc, char* argv[]) {
	vector<Point2D> path;
	//string f = "/Users/armin/Downloads/maze512-32-0.map";
	string f = "/Users/armin/Downloads/mymaze2.map";

	Grid g(1,1);
	g.load(f);

	ShortestPath sp(&g);

	path = sp.bfs_astar(Point2D(2,3), Point2D(22,23));

	if(!path.empty()) {
		cout << "GOAL!! ";
		for(auto p : path)  {
			cout << p << ' ';
		}
		cout << endl;
	}

	return 1;

	cout << "\033[1;31mHello World\033[0m\n";

	unsigned int algo = ASTAR;

	// Select an algorithm
	if(argc == 2) {
		std::string arg = argv[1];
		if((arg == "-d") || (arg == "--dijkstra")) {
			algo = DIJKSTRA;
		} else if((arg == "-g") || (arg == "--greedy")) {
			algo = GREEDY;
		} else if((arg == "-a") || (arg == "--astar")) {
			algo = ASTAR;
		}
		else {
			cout << "Algorithm " << arg << " not recognized. Falling back to default." << endl;
		}
	}

	// Compute the shortest path with the selected algorithm.
	switch(algo) {
		case GREEDY:
			path = run_greedy();
			break;
		case DIJKSTRA:
			path = run_dijkstra();
			break;
		case ASTAR:
			path = run_astar();
			break;

	}
	//TODO	run_bfs_w_early_exit();

	// Print path point by point
	if(!path.empty()) {
		cout << "GOAL!! ";
		for(auto p : path)  {
			cout << p << ' ';
		}
		cout << endl;
	}

	return 0;
}
