//============================================================================
// Name        : astar.cpp
// Author      : Armin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <stdlib.h>

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

vector<Point2D> run_algo(int algo, string f) {
	Grid grid(1,1);
	grid.load(f);
	int off = 3;
	ShortestPath sp(&grid);
	if(!f.empty()) {
		switch(algo) {
		case ASTAR:
			return sp.bfs_astar(Point2D(2,3), Point2D(grid.getWidth()-off,grid.getHeight()-off));
		case DIJKSTRA:
			return sp.bfs_dijkstra(Point2D(2,3), Point2D(grid.getWidth()-off,grid.getHeight()-off));
		case GREEDY:
			return sp.bfs_greedy(Point2D(2,3), Point2D(grid.getWidth()-off,grid.getHeight()-off));
			break;
		}
	}
	vector<Point2D> empty;
	return empty;

}

int main(int argc, char* argv[]) {
	vector<Point2D> path;
	unsigned int algo = ASTAR;
	string f;
	int c;

	cout << "\033[1;31mHello World\033[0m\n";


	// Select an algorithm
	while ((c = getopt (argc, argv, "adgf:")) != -1) {
	    switch (c) {
	      case 'a':
	    	  algo = ASTAR; break;
	      case 'd':
	    	  algo = DIJKSTRA; break;
	      case 'g':
	    	  algo = GREEDY; break;
	      case 'f':
	    	  f = optarg;
	      }
	}

	//string f = "/Users/armin/Downloads/maze512-32-0.map";
	//string f = "/Users/armin/Downloads/mymaze3.map";




	// Compute the shortest path with the selected algorithm.
	path = run_algo(algo, f);

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
