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

inline bool ShortestPath::isvisited(XYPoint p) {
	if (find(visited.begin(), visited.end(), p) != visited.end() ) {
		return true;
	}
	return false;
}

inline bool ShortestPath::infrontier(XYPoint p) {
	if (find(frontier_vec.begin(), frontier_vec.end(), p) != frontier_vec.end() ) {
		return true;
	}
	return false;
}

inline void ShortestPath::visit(XYPoint p) {
	if ( !isvisited(p) ) {
		visited.push_back(p);
	}
}

inline bool ShortestPath::incamefrom(XYPoint p) {
	if ( camefrom.find(p) != camefrom.end() ) {
	  return true;
	}
	return false;
}

inline bool ShortestPath::incostsofar(XYPoint p) {
	if ( costsofar.find(p) != costsofar.end() ) {
	  return true;
	}
	return false;
}

inline void ShortestPath::visitfrom(XYPoint curr, XYPoint from) {
	if ( !incamefrom(curr) ) {
		camefrom.insert({curr, from});
	}
}

void ShortestPath::print_vec(vector<XYPoint> v) {
	for(auto p : v) {
		cout << grid->getWeight(p) << ' ';
	}
	cout << endl;
}

void ShortestPath::print_map(map<XYPoint, XYPoint> v) {
	for(auto it : v) {
		XYPoint p = it.first;
		//cout << grid->getWeight(p)  << " ";
		cout << p << ' ';
	}
	cout << endl;
}


void ShortestPath::print_pq(priorityqueue v) {
	//cout << "hello ";
	priorityqueue vv = v;
	while(!vv.empty()) {
		cout << vv.top() << ' ';
		vv.pop();
	}
	cout << endl;
}



void ShortestPath::dfs_full_traversal(XYPoint start) {
	vector<XYPoint>::iterator it;
	frontier_vec.push_back(start);
	int c=0;

	while(frontier_vec.size()>0) {
		XYPoint p = frontier_vec.back();
		frontier_vec.pop_back();

		visit(p);

		for(auto pp : p.neighbours(*grid)) {
			if(!isvisited(pp) && !infrontier(pp)) {
				frontier_vec.push_back(pp);
				cout << pp << endl;
				c++;
				grid->setWeight(pp, c);
			}
		}
		grid->plot();
		cout << endl;
		cout << frontier_vec.size() << " -> " << grid->getWeight(p) << " " << p << endl;
		printfrontier();
		printvisited();
	}
	cout << "Points visited " << c << endl;
}

void ShortestPath::bfs_full_traversal(XYPoint start) {
	frontier_vec.push_back(start);
	int c=0;

	while(frontier_vec.size()>0) {
		XYPoint p = frontier_vec.front();
		frontier_vec.erase(frontier_vec.begin());

		visit(p);

		for(auto pp : p.neighbours(*grid)) {
			if(!isvisited(pp) && !infrontier(pp)) {
				frontier_vec.push_back(pp);
				cout << pp << endl;
				c++;
				grid->setWeight(pp, c);
			}
		}
		grid->plot();
		cout << endl;
		cout << frontier_vec.size() << " -> " << grid->getWeight(p) << " " << p << endl;
		printfrontier();
		printvisited();
	}
	cout << "Points visited " << c << endl;
}



vector<XYPoint> ShortestPath::bfs_with_early_exit(XYPoint start, XYPoint goal) {
	if(!((grid->inside(start) && grid->inside(goal)))) {
		//TODO throw exception
		return vector<XYPoint>();
	}

	frontier_vec.push_back(start);
	visitfrom(start,start);

	int c=0;
	int vc=0;

	while(frontier_vec.size()>0) {
		XYPoint from = frontier_vec.front();
		frontier_vec.erase(frontier_vec.begin());

		cout << endl;
		cout << frontier_vec.size() << " -> " << grid->getWeight(from) << " " << from << endl;

		if(from==goal) {
			vector<XYPoint> res;
			XYPoint p = from;
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
		grid->plot();
		cout << "frontier = "; printfrontier();
		cout << "visited  = "; print_map(camefrom);
	}
	cout << "Points visited " << c << endl;
	cout << "Points checked " << vc << endl;
	cout << "Map size " << camefrom.size() << endl;

	return vector<XYPoint>();
}


vector<XYPoint> ShortestPath::bfs_dijkstra(XYPoint start, XYPoint goal) {
	vector<XYPoint> res;

	frontier_pq.push(WeightedXYPoint(start,0));
	visitfrom(start,start);
	costsofar[start]=0;

	while(!frontier_pq.empty()) {
		auto curr = frontier_pq.top();
		frontier_pq.pop();

		if(curr==goal) {
			XYPoint p = curr;
			res.push_back(p);
			while(p!=camefrom[p]) {
				p = camefrom[p];
				res.push_back(p);
			}
			cout << costsofar[curr] << endl;
			break;
		}

		for(auto next : curr.neighbours(*grid)) {
			int newcost = costsofar[curr] + grid->getCost(curr, next);
			if( !incostsofar(next) || (newcost<costsofar[next] ))  {
				costsofar[(XYPoint) next]=newcost;
				//costsofar.insert({(XYPoint)next, newcost});
				frontier_pq.push(WeightedXYPoint(next, newcost));
				visitfrom(next,curr);
				cout << next << ' ' << newcost << endl;
			}
		}
		grid->plotw(screen);
		screen->set(start.getX(), start.getY(), 'X', Screen::COL_MNT_P, 0);
		screen->set(goal.getX(), goal.getY(), 'O', Screen::COL_MNT_P, 0);
		getch();
		cout << "frontier = "; print_pq(frontier_pq);
		cout << "visited  = "; print_map(camefrom);
	}

	return res;
}
