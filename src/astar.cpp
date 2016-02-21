//============================================================================
// Name        : astar.cpp
// Author      : Armin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include "points.hpp"

using namespace std;



class ShortestPath {
	vector<XYPoint> frontier;
	vector<XYPoint> visited;
	void visit(XYPoint p);
	bool isvisited(XYPoint p);
	bool infrontier(XYPoint p);
	void printvector(vector<XYPoint> v);
	Grid *grid = nullptr;
public:
	ShortestPath(Grid *g) { grid=g; }
	void depthfirst(XYPoint start, XYPoint goal);
	void printfrontier() { printvector(frontier); };
	void printvisited() { printvector(visited); };
};

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

void ShortestPath::printvector(vector<XYPoint> v) {
	vector<XYPoint>::iterator it;
	for(it=v.begin(); it!=v.end(); ++it) {
		XYPoint p = *it;
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




int main() {

	Grid grid(10,5);

	cout << "Hello World" << endl;
	cout << "\033[1;31mbold red text\033[0m\n";

//	grid.setWeight(20,10,8);
//	grid.setWeight(20,11,8);
//	grid.setWeight(20,12,8);
//	grid.setWeight(20,13,8);
//	grid.setWeight(20,14,8);
//	grid.setWeight(20,15,8);
//	grid.setWeight(21,10,8);
//	grid.setWeight(21,11,8);
//	grid.setWeight(21,12,8);
//	grid.setWeight(21,13,8);
//	grid.setWeight(21,14,8);
//	grid.setWeight(21,15,8);


	ShortestPath bfs(&grid);
	bfs.depthfirst(XYPoint(2,3), XYPoint(3,9));

	XYPoint p(3,3);
	p.neighbours(grid);

	grid.plot();

	return 0;
}
