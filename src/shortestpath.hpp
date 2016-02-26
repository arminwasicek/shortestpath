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

/*! \brief The ShortestPath class implements data structures and algorithms to compute
 * 		   the shortest path in a Grid.
 *
 * 	The class implements the shortest path algorithms Dijstra, Greedy, and A*. It uses
 * 	several data structures from the STL such as vector, map, and priority queues and
 * 	it defines operation to check is points are contained, or other relations between
 * 	points. These relations are mostly of a temporal nature and arise outof the context
 * 	of executing a certain algorithm. \par
 *
 * 	The main purpose of the library is to be educational, it has not been optimized for
 * 	any usage in  a real system.
 *
 * 	\note The descriptions in [here](http://www.redblobgames.com/pathfinding/a-star/introduction.html)
 * 		  were very helpful to implement the search algorithms.
 */
class ShortestPath {
	vector<Point2D> frontier_vec;
	vector<Point2D> visited;
	map<Point2D, Point2D> camefrom;
	map<Point2D, int> costsofar;
	//priority_queue<WeightedXYPoint> frontier_pq;
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

public:

	/*! \brief Constructs a ShortestPath object with respect to a certain grid.
	 *
	 * The constructor allocates all datastructures required for the execution of the
	 * implemented shortest path search algorithms. Moreover, it instantiates a Screen
	 * object that can be used for various output and visualization variants.
	 *
	 * @param[in] g	 The grid on which the algorithms are operating on.
	 */
	ShortestPath(Grid *g) { grid=g; screen = new Screen(grid->getHeight(), grid->getWidth()); }

	/*! \brief Releases resources and empties the temporary data in the containers.
	 */
	~ShortestPath() { cleanup(); }

	/*! \brief Implements a breadth first search that returns as soon as the goal has been
	 * 		   reached.
	 *
	 * @param[in] start		The starting point of the path.
	 * @param[in] goal		The ending point of the path.
	 * \return Returns the shortest path as a list of points.
	 */
	vector<Point2D> bfs_with_early_exit(Point2D start, Point2D goal);

	/*! \brief Implements a shortest path algorithm according to Dijkstra's algorithm.
	 *
	 * @param[in] start		The starting point of the path.
	 * @param[in] goal		The ending point of the path.
	 * \return Returns the shortest path as a list of points.
	 */
	vector<Point2D> bfs_dijkstra(Point2D start, Point2D goal);

	/*! \brief Implements a shortest path algorithm according to the Greedy algorithm.
	 *
	 * @param[in] start		The starting point of the path.
	 * @param[in] goal		The ending point of the path.
	 * \return Returns the shortest path as a list of points.
	 */
	vector<Point2D> bfs_greedy(Point2D start, Point2D goal);

	/*! \brief Implements a shortest path algorithm according to the A* algorithm.
	 *
	 * @param[in] start		The starting point of the path.
	 * @param[in] goal		The ending point of the path.
	 * \return Returns the shortest path as a list of points.
	 */
	vector<Point2D> bfs_astar(Point2D start, Point2D goal);

	/*! \brief Outputs the current state of the frontier vector.
	 */
	void printfrontier() { print_vec(frontier_vec); };

	/*! \brief Outputs the current state of the visited vector.
	 */
	void printvisited() { print_vec(visited); };
};


#endif /* SHORTESTPATH_HPP_ */
