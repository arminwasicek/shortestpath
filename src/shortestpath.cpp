/*
 * shortestpath.cpp
 *
 *  Created on: Feb 21, 2016
 *      Author: armin
 */

#include "shortestpath.hpp"

using namespace std;


bool ShortestPath::isvisited(XYPoint p) {
	if (find(visited.begin(), visited.end(), p) != visited.end() ) {
		return true;
	}
	return false;
}

bool ShortestPath::infrontier(XYPoint p) {
	if (find(frontier.begin(), frontier.end(), p) != frontier.end() ) {
		return true;
	}
	return false;
}

void ShortestPath::visit(XYPoint p) {
	if ( !isvisited(p) ) {
		visited.push_back(p);
	}
}

bool ShortestPath::isvisitedmap(XYPoint p) {
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
	frontier.push_back(start);
	int c=0;

	while(frontier.size()>0) {
		XYPoint p = frontier.back();
		frontier.pop_back();

		visit(p);

		for(auto pp : p.neighbours(*grid)) {
			if(!isvisited(pp) && !infrontier(pp)) {
				frontier.push_back(pp);
				cout << pp << endl;
				c++;
				grid->setWeight(pp, c);
			}
		}
		grid->plot();
		cout << endl;
		cout << frontier.size() << " -> " << grid->getWeight(p) << " " << p << endl;
		printfrontier();
		printvisited();
	}
	cout << "Points visited " << c << endl;
}

void ShortestPath::breadthfirst(XYPoint start, XYPoint goal) {
	frontier.push_back(start);
	int c=0;

	while(frontier.size()>0) {
		XYPoint p = frontier.front();
		frontier.erase(frontier.begin());

		visit(p);

		for(auto pp : p.neighbours(*grid)) {
			if(!isvisited(pp) && !infrontier(pp)) {
				frontier.push_back(pp);
				cout << pp << endl;
				c++;
				grid->setWeight(pp, c);
			}
		}
		grid->plot();
		cout << endl;
		cout << frontier.size() << " -> " << grid->getWeight(p) << " " << p << endl;
		printfrontier();
		printvisited();
	}
	cout << "Points visited " << c << endl;
}



void ShortestPath::bfspath(XYPoint start, XYPoint goal) {
	if(!((grid->inside(start) && grid->inside(goal)))) {
		//TODO throw exception
		return ;
	}

	frontier.push_back(start);
	visitmap(start,start);

	int c=0;
	int vc=0;

	while(frontier.size()>0) {
		XYPoint from = frontier.front();
		frontier.erase(frontier.begin());

		cout << endl;
		cout << frontier.size() << " -> " << grid->getWeight(from) << " " << from << endl;

		if(from==goal) {
			cout << "GOAL!! ";
			XYPoint p = from;
			cout << p << ' ';
			while(p!=camefrom[p]) {
				p = camefrom[p];
				cout << p << ' ';
			}
			cout << endl;
			return ;
		}

		for(auto curr: from.neighbours(*grid)) {
			++vc;
			if(!isvisitedmap(curr) && !infrontier(curr)) {
				frontier.push_back(curr);
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
}

void ShortestPath::bfspath2(XYPoint start, XYPoint goal) {
	map<XYPoint, XYPoint> cf;
	int l=0;
	frontier.push_back(start);
	cf.insert({start, start}); //visit(start);
	while(frontier.size()>0) {
		XYPoint from = frontier.front();
		frontier.erase(frontier.begin());
		cout << l << ' ' << from << endl;  l++;
		vector<XYPoint> n = from.neighbours(*grid);
		for(auto curr : n) {
			if ( cf.find(curr) == cf.end() ) {    //if(!isvisited(curr)) {
				frontier.push_back(curr);
				cf.insert({curr, curr}); //visit(curr);
			}
		}
	}
}
