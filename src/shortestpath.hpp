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

/*! \brief Generic class that implements the data structures and access methods for the shortest path search.
 *
 * Subclass and overwrite the runbfs method with a specific algorithm.
 */
class ShortestPath {
protected:
	vector<Point2D> frontier_vec;		/*!< A vector to store points for representing the current frontier */
	vector<Point2D> visited;			/*!< A vector to store the points visited. */
	map<Point2D, Point2D> camefrom;		/*!< A map to track the history of the algorithm */
	map<Point2D, int> costsofar;		/*!< A map that stores the costs incurred so far for a point */
	weightedpointpq frontier_pq;		/*!< A priority queue to store points for representing the current frontier */
	Grid *grid = nullptr;				/*!< The grid representing the context in that the algorithm works */
	Screen *screen = nullptr;			/*!< The screen abstracts the IO operations for the algorithm. */

	/*! \brief Marks a point as visited in #frontier_vec. */
	void visit(Point2D p);
	/*! \brief Checks, if a point has been visited in #visited. */
	bool isvisited(Point2D p);
	/*! \brief Checks, if a point has been visited in #camefrom. */
	bool incamefrom(Point2D p);
	/*! \brief Checks, if a point has been assigned a cost in #costsofar . */
	bool incostsofar(Point2D p);
	/*! \brief Checks, if a point has been assigned a cost in #costsofar . */
	void visitfrom(Point2D curr, Point2D from);
	/*! \brief Checks, if a point has been visited in #frontier_vec. */
	bool infrontier(Point2D p);
	/*! \brief Outputs a vector using cout. */
	void print_vec(vector<Point2D> v);
	/*! \brief Outputs a map using cout. */
	void print_map(map<Point2D, Point2D> v);
	/*! \brief Outputs a priority queue using cout. */
	void print_pq(weightedpointpq v);
	/*! \brief Plots the points in the priority queue using ncurses. */
	void plot_pq(weightedpointpq v);
	/*! \brief Free all resources and empty all data structures. */
	void cleanup();

	/*! \brief Outputs the current state of the frontier vector.
	 */
	void printfrontier() { print_vec(frontier_vec); };

	/*! \brief Outputs the current state of the visited vector.
	 */
	void printvisited() { print_vec(visited); };

public:
	ShortestPath(Grid *g) { grid=g; screen = new Screen(grid->getHeight(), grid->getWidth()); }
	virtual ~ShortestPath() { cleanup(); }
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
