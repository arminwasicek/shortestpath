//============================================================================
// Name        : astar.cpp
// Author      : Armin
// Version     : v0.1
// Copyright   : Copyright (c) 2016, Armin, FreeBSD License
// Description : Framework to compare different shortest path finding algorithms.
//============================================================================

#include <iostream>
#include <vector>
#include <stdlib.h>

#include "points.hpp"
#include "shortestpath.hpp"
#include "screen.hpp"

using namespace std;

/*! This enum specifies the algorithms available */
enum algo {
	DIJKSTRA = 0,		/*!< Dijkstra's uses breadth first search. */
	GREEDY,				/*!< Greedy minimizes the distance. */
	ASTAR				/*!< A* combines bfs with min distance. */
};



/*! \brief Runs the selected shortest path search algorithm.
 *
 * Runs the selected shortest path search algorithm. If no algorithm is
 * selected, or the selection is not available, an empty path is returned.
 * If no map has been specified, an empty 10x10 grid is used per default.
 *
 * @param[in] algo	The algorithm selected.
 * @param[in] file	Filename to read a map.
 *
 * \return A vector containing the sequence of points between start and goal.
 */
vector<Point2D> run_algo(int algo, string file) {
	Grid grid(10,10);
	if(!file.empty()) {
		grid.load(file);
	}
	int off = 3;
	ShortestPath sp(&grid);

	switch(algo) {
		case ASTAR:
			return sp.bfs_astar(Point2D(2,3), Point2D(grid.getWidth()-off,grid.getHeight()-off));
		case DIJKSTRA:
			return sp.bfs_dijkstra(Point2D(2,3), Point2D(grid.getWidth()-off,grid.getHeight()-off));
		case GREEDY:
			return sp.bfs_greedy(Point2D(2,3), Point2D(grid.getWidth()-off,grid.getHeight()-off));
			break;
	}

	vector<Point2D> empty;
	return empty;
}

/*!
 * The main function parses arguments and invokes the shortest path search.
 */
int main(int argc, char* argv[]) {
	vector<Point2D> path;				/*!< Stores the path found */
	unsigned int algo = ASTAR;			/*!< Algorithm selection, defaults to A* */
	string f;							/*!< Map file name */
	int c;

	cout << "\033[1;31mHello World\033[0m\n";
	cout << "Press button to continue..." << endl;
	getchar();


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

	// Compute the shortest path with the selected algorithm.
	path = run_algo(algo, f);

	// Print path point by point
	if(!path.empty()) {
		cout << "GOAL!! ";
		for(auto p : path)  {
			cout << p << ' ';
		}
		cout << endl;
	}

	// Everything went well.
	return 0;
}
