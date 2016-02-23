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

inline bool ShortestPath::isvisitedmap(XYPoint p) {
	if ( camefrom.find(p) != camefrom.end() ) {
	  return true;
	}
	return false;
}

inline void ShortestPath::visitmap(XYPoint curr, XYPoint from) {
	if ( !isvisitedmap(curr) ) {
		camefrom.insert({curr, from});
	}
}

void ShortestPath::printvector(vector<XYPoint> v) {
	for(auto p : v) {
		cout << grid->getWeight(p) << ' ';
	}
	cout << endl;
}

void ShortestPath::printmap(map<XYPoint, XYPoint> v) {
	for(auto it : v) {
		XYPoint p = it.first;
		cout << grid->getWeight(p)  << " ";
	}
	cout << endl;
}


void ShortestPath::depthfirst(XYPoint start, XYPoint goal) {
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

void ShortestPath::breadthfirst(XYPoint start, XYPoint goal) {
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
	visitmap(start,start);

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
			if(!isvisitedmap(curr)) {
				frontier_vec.push_back(curr);
				visitmap(curr,from);
				cout << curr << endl;
				c++;
				grid->setWeight(curr, c);
			}
		}
		grid->plot();
		cout << "frontier = "; printfrontier();
		cout << "visited  = "; printmap(camefrom);
	}
	cout << "Points visited " << c << endl;
	cout << "Points checked " << vc << endl;
	cout << "Map size " << camefrom.size() << endl;

	return vector<XYPoint>();
}

void ShortestPath::bfspath2(XYPoint start, XYPoint goal) {
	map<XYPoint, XYPoint> cf;
	int l=0;
	frontier_vec.push_back(start);
	cf.insert({start, start}); //visit(start);
	while(frontier_vec.size()>0) {
		XYPoint from = frontier_vec.front();
		frontier_vec.erase(frontier_vec.begin());
		cout << l << ' ' << from << endl;  l++;
		vector<XYPoint> n = from.neighbours(*grid);
		for(auto curr : n) {
			if ( cf.find(curr) == cf.end() ) {    //if(!isvisited(curr)) {
				frontier_vec.push_back(curr);
				cf.insert({curr, curr}); //visit(curr);
			}
		}
	}
}

vector<XYPoint> ShortestPath::bfs_dijkstra(XYPoint start, XYPoint goal) {
	vector<XYPoint> res;

	frontier_pq.push(WeightedXYPoint(start,0));




	return res;
}
