/*
 * shortestpath.cpp
 *
 *  Created on: Feb 21, 2016
 *      Author: armin
 */

#include "shortestpath.hpp"

using namespace std;

void ShortestPathDS::cleanup() {
	frontier_vec.clear();
	visited.clear();
	camefrom.clear();
	delete screen;
}

inline bool ShortestPathDS::isvisited(Point2D p) {
	if (find(visited.begin(), visited.end(), p) != visited.end() ) {
		return true;
	}
	return false;
}

inline bool ShortestPathDS::infrontier(Point2D p) {
	if (find(frontier_vec.begin(), frontier_vec.end(), p) != frontier_vec.end() ) {
		return true;
	}
	return false;
}

inline void ShortestPathDS::visit(Point2D p) {
	if ( !isvisited(p) ) {
		visited.push_back(p);
	}
}

inline bool ShortestPathDS::incamefrom(Point2D p) {
	if ( camefrom.find(p) != camefrom.end() ) {
	  return true;
	}
	return false;
}

inline bool ShortestPathDS::incostsofar(Point2D p) {
	if ( costsofar.find(p) != costsofar.end() ) {
	  return true;
	}
	return false;
}

inline void ShortestPathDS::visitfrom(Point2D curr, Point2D from) {
	if ( !incamefrom(curr) ) {
		camefrom.insert({curr, from});
	}
}

void ShortestPathDS::print_vec(vector<Point2D> v) {
	for(auto p : v) {
		cout << grid->getWeight(p) << ' ';
	}
	cout << endl;
}

void ShortestPathDS::print_map(map<Point2D, Point2D> v) {
	for(auto it : v) {
		Point2D p = it.first;
		//cout << grid->getWeight(p)  << " ";
		cout << p << ' ';
	}
	cout << endl;
}

/*! \note Priority queues in the STL cannot be traversed using an iterator. Therefore,
 * 	      the priority queue is copied first in a temporary queue which is emptied
 * 	      and printed element by element. This might not be the most efficient way to
 * 	      to this.
 */
void ShortestPathDS::print_pq(weightedpointpq v) {
	weightedpointpq vv = v;
	while(!vv.empty()) {
		cout << vv.top() << ' ';
		vv.pop();
	}
	cout << endl;
}

/*! \note Priority queues in the STL cannot be traversed using an iterator. Therefore,
 * 	      the priority queue is copied first in a temporary queue which is emptied
 * 	      and printed element by element. This might not be the most efficient way to
 * 	      to this.
 */
void ShortestPathDS::plot_pq(weightedpointpq v) {
	weightedpointpq vv = v;
	while(!vv.empty()) {
		Point2D p = vv.top();
		vv.pop();
		screen->set(p.getX(), p.getY(), '#', 0, 0);
	}
}

/*!
 * Breath first search treats all the points the same. They are enqueued and
 * processed on a first come first serve basis.
 */
vector<Point2D> ShortestPathBFS::bfs_with_early_exit(Point2D start, Point2D goal) {
	if(!((grid->inside(start) && grid->inside(goal)))) {
		//TODO throw exception
		return vector<Point2D>();
	}

	// Add the first point to the vector serving as the frontier queue
	frontier_vec.push_back(start);
	visitfrom(start,start);

	int c=0;
	int vc=0;

	// Repeat until there are points in the frontier
	while(frontier_vec.size()>0) {
		Point2D from = frontier_vec.front();
		frontier_vec.erase(frontier_vec.begin());

		cout << endl;
		cout << frontier_vec.size() << " -> " << grid->getWeight(from) << " " << from << endl;

		// Check, if goal has been reached
		if(from==goal) {
			vector<Point2D> res;
			Point2D p = from;
			res.push_back(p);
			// Fill the vector for the shortest path
			while(p!=camefrom[p]) {
				p = camefrom[p];
				res.push_back(p);
			}
			return res;
		}

		// Get all neighbors that have not yet been visited and put them in the queue.
		for(auto curr: from.neighbours(*grid)) {
			++vc;
			if(!incamefrom(curr)) {
				frontier_vec.push_back(curr);
				visitfrom(curr,from);
				cout << curr << endl;
				c++;
				grid->setWeight(curr, c);
			}
		}
	}
	return vector<Point2D>(); // Goal has not been found, return empty path list.
}

/*!
 * Dijkstra's algorithm uses breath first search and optimizes based on a cost
 * function between points. Thus, points with a lower cost are retrieved earlier
 * during execution from the priority queue.
 *
 * \note The method implements a delay after each processed point for visualization purposes.
 */
vector<Point2D> ShortestPathDijkstra::bfs_dijkstra(Point2D start, Point2D goal) {
	vector<Point2D> res;

	// Add the first point to the priority queue serving as the frontier
	frontier_pq.push(WeightedPoint2D(start,0));
	visitfrom(start,start);
	costsofar[start]=0;

	// Repeat until there are points in the frontier
	while(!frontier_pq.empty()) {
		auto curr = frontier_pq.top();
		frontier_pq.pop();

		// Check, if goal has been reached
		if(curr==goal) {
			cout << "found" << endl;
			Point2D p = curr;
			res.push_back(p);
			while(p!=camefrom[p]) {
				p = camefrom[p];
				res.push_back(p);
			}
			return res;
		}

		// Get all neighbors that have not yet been visited and put them in the frontier,
		// given that they are either new, or this path is cheaper than the one stored.
		for(auto next : curr.neighbours(*grid)) {
			int newcost = costsofar[curr] + grid->getCost(curr, next);
			if( !incostsofar(next) || (newcost<costsofar[next] ))  {
				costsofar[(Point2D) next]=newcost;
				frontier_pq.push(WeightedPoint2D(next, newcost));
				visitfrom(next,curr);
			}
		}
		// Some display comands.
		grid->plotw(screen);
		screen->set(start.getX(), start.getY(), 'X', Screen::COL_MNT_P, 0);
		screen->set(goal.getX(), goal.getY(), 'O', Screen::COL_MNT_P, 0);
		plot_pq(frontier_pq);
		screen->update();
		//getch();
		usleep(100000);
	}
	return res;
}



/*!
 * The Greedy algorithm optimizes based on the distance of the current point to
 * the goal. The next point processed is always the one with the shortest distance
 * to the goal.
 *
 * \note The method implements a delay after each processed point for visualization purposes.
 */
vector<Point2D> ShortestPathGreedy::bfs_greedy(Point2D start, Point2D goal) {
	vector<Point2D> res;

	// Add the first point to the priority queue serving as the frontier
	frontier_pq.push(WeightedPoint2D(start,0));
	visitfrom(start,start);
	costsofar[start]=0;

	// Repeat until there are points in the frontier
	while(!frontier_pq.empty()) {
		auto curr = frontier_pq.top();
		frontier_pq.pop();

		// Check, if goal has been reached
		if(curr==goal) {
			cout << "found" << endl;
			Point2D p = curr;
			res.push_back(p);
			while(p!=camefrom[p]) {
				p = camefrom[p];
				res.push_back(p);
			}
			return res;
		}

		// Get all neighbors that have not yet been visited and put them in the queue.
		for(auto next : curr.neighbours(*grid)) {
			if(!incamefrom(next))  {
				// Compute a priority based on the distance to the goal.
				int priority = next.dist(goal, Point2D::MANHATTEN);
				frontier_pq.push(WeightedPoint2D(next, priority));
				visitfrom(next,curr);
			}
		}
		// Some display comands.
		grid->plotw(screen);
		screen->set(start.getX(), start.getY(), 'X', Screen::COL_MNT_P, 0);
		screen->set(goal.getX(), goal.getY(), 'O', Screen::COL_MNT_P, 0);
		plot_pq(frontier_pq);
		screen->update();
		//getch();
		usleep(100000);
	}
	return res;
}




/*!
 * The A* algorithm combines the best from Dijkstra and Greedy algorithms. It adds new points
 * based on their current shortest path, but also their distance to the goal. This makes the
 * algorithm efficient and robust, even on maps with difficult features.
 *
 * \note The method implements a delay after each processed point for visualization purposes.
 */
vector<Point2D> ShortestPathAstar::bfs_astar(Point2D start, Point2D goal) {
	vector<Point2D> res;

	// Add the first point to the priority queue serving as the frontier
	frontier_pq.push(WeightedPoint2D(start,0));
	visitfrom(start,start);
	costsofar[start]=0;

	// Repeat until there are points in the frontier
	while(!frontier_pq.empty()) {
		auto curr = frontier_pq.top();
		frontier_pq.pop();

		// Check, if goal has been reached
		if(curr==goal) {
			//cout << "found" << endl;
			Point2D p = curr;
			res.push_back(p);
			while(p!=camefrom[p]) {
				p = camefrom[p];
				res.push_back(p);
			}
			return res;
		}

		// Get all neighbors that have not yet been visited and put them in the frontier,
		// given that they are either new, or this path is cheaper than the one stored.
		for(auto next : curr.neighbours(*grid)) {
			int newcost = costsofar[curr] + grid->getCost(curr, next);
			if( !incostsofar(next) || (newcost<costsofar[next] ))  {
				costsofar[(Point2D) next] = newcost;
				// Prioritize the point nearer to the goal
				int priority = newcost + next.dist(goal, Point2D::MANHATTEN);
				frontier_pq.push(WeightedPoint2D(next, priority));
				visitfrom(next,curr);
			}
		}
		// Some display commands.
		grid->plotw(screen);
		screen->set(start.getX(), start.getY(), 'X', Screen::COL_MNT_P, 0);
		screen->set(goal.getX(), goal.getY(), 'O', Screen::COL_MNT_P, 0);
		plot_pq(frontier_pq);
		screen->update();
		//getch();
		usleep(100000);
	}
	return res;
}

