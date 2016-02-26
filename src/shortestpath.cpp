/*
 * shortestpath.cpp
 *
 *  Created on: Feb 21, 2016
 *      Author: armin
 */

#include "shortestpath.hpp"

using namespace std;

void ShortestPath::cleanup() {
	frontier_vec.clear();
	visited.clear();
	camefrom.clear();
	delete screen;
}

inline bool ShortestPath::isvisited(Point2D p) {
	if (find(visited.begin(), visited.end(), p) != visited.end() ) {
		return true;
	}
	return false;
}

inline bool ShortestPath::infrontier(Point2D p) {
	if (find(frontier_vec.begin(), frontier_vec.end(), p) != frontier_vec.end() ) {
		return true;
	}
	return false;
}

inline void ShortestPath::visit(Point2D p) {
	if ( !isvisited(p) ) {
		visited.push_back(p);
	}
}

inline bool ShortestPath::incamefrom(Point2D p) {
	if ( camefrom.find(p) != camefrom.end() ) {
	  return true;
	}
	return false;
}

inline bool ShortestPath::incostsofar(Point2D p) {
	if ( costsofar.find(p) != costsofar.end() ) {
	  return true;
	}
	return false;
}

inline void ShortestPath::visitfrom(Point2D curr, Point2D from) {
	if ( !incamefrom(curr) ) {
		camefrom.insert({curr, from});
	}
}

void ShortestPath::print_vec(vector<Point2D> v) {
	for(auto p : v) {
		cout << grid->getWeight(p) << ' ';
	}
	cout << endl;
}

void ShortestPath::print_map(map<Point2D, Point2D> v) {
	for(auto it : v) {
		Point2D p = it.first;
		//cout << grid->getWeight(p)  << " ";
		cout << p << ' ';
	}
	cout << endl;
}


void ShortestPath::print_pq(priorityqueue v) {
	priorityqueue vv = v;
	while(!vv.empty()) {
		cout << vv.top() << ' ';
		vv.pop();
	}
	cout << endl;
}

void ShortestPath::plot_pq(priorityqueue v) {
	priorityqueue vv = v;
	while(!vv.empty()) {
		Point2D p = vv.top();
		vv.pop();
		screen->set(p.getX(), p.getY(), '#', 0, 0);
	}
}


vector<Point2D> ShortestPath::bfs_with_early_exit(Point2D start, Point2D goal) {
	if(!((grid->inside(start) && grid->inside(goal)))) {
		//TODO throw exception
		return vector<Point2D>();
	}

	frontier_vec.push_back(start);
	visitfrom(start,start);

	int c=0;
	int vc=0;

	while(frontier_vec.size()>0) {
		Point2D from = frontier_vec.front();
		frontier_vec.erase(frontier_vec.begin());

		cout << endl;
		cout << frontier_vec.size() << " -> " << grid->getWeight(from) << " " << from << endl;

		if(from==goal) {
			vector<Point2D> res;
			Point2D p = from;
			res.push_back(p);
			while(p!=camefrom[p]) {
				p = camefrom[p];
				res.push_back(p);
			}
			return res;
		}

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
	return vector<Point2D>();
}


vector<Point2D> ShortestPath::bfs_dijkstra(Point2D start, Point2D goal) {
	vector<Point2D> res;

	frontier_pq.push(WeightedPoint2D(start,0));
	visitfrom(start,start);
	costsofar[start]=0;

	while(!frontier_pq.empty()) {
		auto curr = frontier_pq.top();
		frontier_pq.pop();

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

		for(auto next : curr.neighbours(*grid)) {
			int newcost = costsofar[curr] + grid->getCost(curr, next);
			if( !incostsofar(next) || (newcost<costsofar[next] ))  {
				costsofar[(Point2D) next]=newcost;
				frontier_pq.push(WeightedPoint2D(next, newcost));
				visitfrom(next,curr);
			}
		}
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





vector<Point2D> ShortestPath::bfs_greedy(Point2D start, Point2D goal) {
	vector<Point2D> res;

	frontier_pq.push(WeightedPoint2D(start,0));
	visitfrom(start,start);
	costsofar[start]=0;

	while(!frontier_pq.empty()) {
		auto curr = frontier_pq.top();
		frontier_pq.pop();

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

		for(auto next : curr.neighbours(*grid)) {
			if(!incamefrom(next))  {
				int priority = next.dist(goal, Point2D::MANHATTEN);
				frontier_pq.push(WeightedPoint2D(next, priority));
				visitfrom(next,curr);
			}
		}
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





vector<Point2D> ShortestPath::bfs_astar(Point2D start, Point2D goal) {
	vector<Point2D> res;

	frontier_pq.push(WeightedPoint2D(start,0));
	visitfrom(start,start);
	costsofar[start]=0;

	while(!frontier_pq.empty()) {
		auto curr = frontier_pq.top();
		frontier_pq.pop();

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

		for(auto next : curr.neighbours(*grid)) {
			int newcost = costsofar[curr] + grid->getCost(curr, next);
			if( !incostsofar(next) || (newcost<costsofar[next] ))  {
				costsofar[(Point2D) next] = newcost;
				int priority = newcost + next.dist(goal, Point2D::MANHATTEN);
				frontier_pq.push(WeightedPoint2D(next, priority));
				visitfrom(next,curr);
			}
		}
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

