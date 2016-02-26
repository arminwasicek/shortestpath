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
#include <unistd.h>

#include "points.hpp"
#include "screen.hpp"

typedef priority_queue<WeightedPoint2D,vector<WeightedPoint2D>, WeightedPoint2D::compare> priorityqueue;

class ShortestPath {
	vector<Point2D> frontier_vec;
	vector<Point2D> visited;
	map<Point2D, Point2D> camefrom;
	map<Point2D, int> costsofar;
	//priority_queue<WeightedXYPoint> frontier_pq;
	priorityqueue frontier_pq;
	Grid *grid = nullptr;
	Screen *screen = nullptr;
	void visit(Point2D p);
	bool isvisited(Point2D p);
	bool incamefrom(Point2D p);
	bool incostsofar(Point2D p);
	void visitfrom(Point2D curr, Point2D from);
	bool infrontier(Point2D p);
	void print_vec(vector<Point2D> v);
	void print_map(map<Point2D, Point2D> v);
	void print_pq(priorityqueue v);
	void plot_pq(priorityqueue v);
	void cleanup();

public:

	ShortestPath(Grid *g) { grid=g; screen = new Screen(grid->getHeight(), grid->getWidth()); }
	~ShortestPath() { cleanup(); }
	void dfs_full_traversal(Point2D start);
	void bfs_full_traversal(Point2D start);
	vector<Point2D> bfs_with_early_exit(Point2D start, Point2D goal);
	vector<Point2D> bfs_dijkstra(Point2D start, Point2D goal);
	vector<Point2D> bfs_greedy(Point2D start, Point2D goal);
	vector<Point2D> bfs_astar(Point2D start, Point2D goal);
	void printfrontier() { print_vec(frontier_vec); };
	void printvisited() { print_vec(visited); };
};


#endif /* SHORTESTPATH_HPP_ */
