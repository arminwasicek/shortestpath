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

bool ShortestPath::isvisitedmap(XYPoint p) {
	int n = camefrom.count(p);
	if (n>0)  {
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

void ShortestPath::visitmap(XYPoint curr, XYPoint from) {
	if ( !isvisitedmap(curr) ) {
		camefrom[curr] = from;
	}
}

void ShortestPath::printvector(vector<XYPoint> v) {
	vector<XYPoint>::iterator it;
	for(it=v.begin(); it!=v.end(); ++it) {
		XYPoint p = *it;
		cout << grid->getWeight(p) << ' ';
	}
	cout << endl;
}

void ShortestPath::printmap(map<const XYPoint, XYPoint> v) {
	map<const XYPoint, XYPoint>::iterator it;
	for(it=v.begin(); it!=v.end(); ++it) {
		XYPoint p = it->first;
		cout << grid->getWeight(p) << ' ';
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
		vector<XYPoint> n = p.neighbours(*grid);

		for(it=n.begin(); it!=n.end(); ++it) {
			XYPoint pp = *it;
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
	vector<XYPoint>::iterator it;
	frontier.push_back(start);
	int c=0;

	while(frontier.size()>0) {
		XYPoint p = frontier.front();
		frontier.erase(frontier.begin());

		visit(p);
		vector<XYPoint> n = p.neighbours(*grid);

		for(it=n.begin(); it!=n.end(); ++it) {
			XYPoint pp = *it;
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
	vector<XYPoint>::iterator it;

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
		}

		vector<XYPoint> n = from.neighbours(*grid);

		for(it=n.begin(); it!=n.end(); ++it) {
			XYPoint curr = *it; ++vc;
			if(!isvisitedmap(curr)) {
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
