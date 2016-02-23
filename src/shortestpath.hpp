/*
 * shortestpath.hpp
 *
 *  Created on: Feb 21, 2016
 *      Author: armin
 */

#ifndef SHORTESTPATH_HPP_
#define SHORTESTPATH_HPP_

#include <map>

#include "points.hpp"



class ShortestPath {
	vector<XYPoint> frontier;
	vector<XYPoint> visited;
	map<XYPoint, XYPoint> camefrom;
	Grid *grid = nullptr;
	void visit(XYPoint p);
	bool isvisited(XYPoint p);
	inline bool isvisitedmap(XYPoint p);
	void visitmap(XYPoint curr, XYPoint from);
	bool infrontier(XYPoint p);
	void printvector(vector<XYPoint> v);
	void printmap(map<XYPoint, XYPoint> v);
	void cleanup();

public:

	ShortestPath(Grid *g) { grid=g; }
	~ShortestPath() { cleanup(); }
	void depthfirst(XYPoint start, XYPoint goal);
	void breadthfirst(XYPoint start, XYPoint goal);
	vector<XYPoint> bfs_with_early_exit(XYPoint start, XYPoint goal);
	void bfspath2(XYPoint start, XYPoint goal);
	void printfrontier() { printvector(frontier); };
	void printvisited() { printvector(visited); };
};


#endif /* SHORTESTPATH_HPP_ */
