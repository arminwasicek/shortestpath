/*
 * shortestpath.hpp
 *
 *  Created on: Feb 21, 2016
 *      Author: armin
 */

#ifndef SHORTESTPATH_HPP_
#define SHORTESTPATH_HPP_

#include <map>
#include <queue>

#include "points.hpp"
#include "screen.hpp"

typedef priority_queue<WeightedXYPoint,vector<WeightedXYPoint>, WeightedXYPoint::compare> priorityqueue;

class ShortestPath {
	vector<XYPoint> frontier_vec;
	vector<XYPoint> visited;
	map<XYPoint, XYPoint> camefrom;
	map<XYPoint, int> costsofar;
	//priority_queue<WeightedXYPoint> frontier_pq;
	priorityqueue frontier_pq;
	Grid *grid = nullptr;
	Screen *screen = nullptr;
	void visit(XYPoint p);
	bool isvisited(XYPoint p);
	bool incamefrom(XYPoint p);
	bool incostsofar(XYPoint p);
	void visitfrom(XYPoint curr, XYPoint from);
	bool infrontier(XYPoint p);
	void print_vec(vector<XYPoint> v);
	void print_map(map<XYPoint, XYPoint> v);
	void print_pq(priorityqueue v);
	void plot_pq(priorityqueue v);
	void cleanup();

public:

	ShortestPath(Grid *g) { grid=g; screen = new Screen(grid->getHeight(), grid->getWidth()); }
	~ShortestPath() { cleanup(); }
	void dfs_full_traversal(XYPoint start);
	void bfs_full_traversal(XYPoint start);
	vector<XYPoint> bfs_with_early_exit(XYPoint start, XYPoint goal);
	vector<XYPoint> bfs_dijkstra(XYPoint start, XYPoint goal);
	void printfrontier() { print_vec(frontier_vec); };
	void printvisited() { print_vec(visited); };
};


#endif /* SHORTESTPATH_HPP_ */
