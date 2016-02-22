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
	void visit(XYPoint p);
	bool isvisited(XYPoint p);
	bool infrontier(XYPoint p);
	void printvector(vector<XYPoint> v);
	Grid *grid = nullptr;
public:
	ShortestPath(Grid *g) { grid=g; }
	void depthfirst(XYPoint start, XYPoint goal);
	void breadthfirst(XYPoint start, XYPoint goal);
	void bfspath(XYPoint start, XYPoint goal);
	void printfrontier() { printvector(frontier); };
	void printvisited() { printvector(visited); };
};


#endif /* SHORTESTPATH_HPP_ */
