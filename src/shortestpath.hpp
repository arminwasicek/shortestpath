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

/*! \brief Type shorthand for a priority queue storing weighted points.
 */
typedef priority_queue<WeightedPoint2D,vector<WeightedPoint2D>, WeightedPoint2D::compare> weightedpointpq;

class ShortestPath {
protected:
	vector<Point2D> frontier_vec;
	vector<Point2D> visited;
	map<Point2D, Point2D> camefrom;
	map<Point2D, int> costsofar;
	weightedpointpq frontier_pq;
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
	void print_pq(weightedpointpq v);
	void plot_pq(weightedpointpq v);
	void cleanup();

	/*! \brief Outputs the current state of the frontier vector.
	 */
	void printfrontier() { print_vec(frontier_vec); };

	/*! \brief Outputs the current state of the visited vector.
	 */
	void printvisited() { print_vec(visited); };

public:
	ShortestPath(Grid *g) { grid=g; screen = new Screen(grid->getHeight(), grid->getWidth()); cout << "Constructor " << g << endl;}
	virtual ~ShortestPath() { cleanup(); cout << "deleting ShortestPath" << endl;}
	/*! \brief Implements a shortest path search algorithm based on breadth first search.
	 *
	 * Concrete implementations have to subclass ShortestPath.
	 *
	 * @param[in] start		The starting point of the path.
	 * @param[in] goal		The ending point of the path.
	 * \return Returns the shortest path as a list of points.
	 */
	virtual vector<Point2D> runbfs(Point2D start, Point2D goal) {cout << "ShortestPath runbfs" << endl; vector<Point2D> res; return res;};
};


/*! \brief Implements a breadth first search that returns as soon as the goal has been
 * 		   reached.
 */
class ShortestPathBFS : public ShortestPath {
public:
	using ShortestPath::ShortestPath;
	~ShortestPathBFS() {};
	vector<Point2D> runbfs(Point2D start, Point2D goal);
};

/*! \brief Implements a shortest path algorithm according to Dijkstra's algorithm.
 */
class ShortestPathDijkstra : public ShortestPath {
public:
	using ShortestPath::ShortestPath;
	~ShortestPathDijkstra() {};
	vector<Point2D> runbfs(Point2D start, Point2D goal);
};

/*! \brief Implements a shortest path algorithm according to the Greedy algorithm.
 */
class ShortestPathGreedy : public ShortestPath {
public:
	using ShortestPath::ShortestPath;
	~ShortestPathGreedy() {};
	vector<Point2D> runbfs(Point2D start, Point2D goal);
};

/*! \brief Implements a shortest path algorithm according to the A* algorithm.
 */
class ShortestPathAstar : public ShortestPath {
public:
	using ShortestPath::ShortestPath;
	~ShortestPathAstar() {};
	vector<Point2D> runbfs(Point2D start, Point2D goal);
};

#endif /* SHORTESTPATH_HPP_ */
