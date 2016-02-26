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
#include "shortestpath.hpp"
#include "screen.hpp"

using namespace std;


void run_dfs()  {
	Grid grid(10,5);
	ShortestPath dfs(&grid);
	dfs.dfs_full_traversal(XYPoint(2,3));
}

void run_bfs()  {
	Grid grid(10,5);
	ShortestPath bfs(&grid);
	bfs.bfs_full_traversal(XYPoint(2,3));
}

void run_bfs_w_early_exit()  {
	Grid grid(10,5);
	ShortestPath bfs(&grid);
	auto path = bfs.bfs_with_early_exit(XYPoint(2,3), XYPoint(9,3));
	cout << "GOAL!! ";
	for(auto p : path)  {
		cout << p << ' ';
	}
	cout << endl;
}

vector<XYPoint> run_dijkstra() {
	Grid grid(10,5);
	ShortestPath bfs(&grid);

	grid.setWeight(4,1,1);
	grid.setWeight(4,2,1);
	grid.setWeight(4,3,1);
	grid.setWeight(5,1,2);
	grid.setWeight(5,2,2);
	grid.setWeight(5,3,2);
	grid.setWeight(6,1,1);
	grid.setWeight(6,2,1);
	grid.setWeight(6,3,1);

	return bfs.bfs_dijkstra(XYPoint(2,3), XYPoint(9,3));
}

vector<XYPoint> run_greedy() {
	Grid grid(10,5);
	ShortestPath bfs(&grid);

	grid.setWeight(4,1,3);
	grid.setWeight(4,2,3);
	grid.setWeight(4,3,3);
	grid.setWeight(5,1,9);
	grid.setWeight(5,2,9);
	grid.setWeight(5,3,9);
	grid.setWeight(6,1,3);
	grid.setWeight(6,2,3);
	grid.setWeight(6,3,3);

	return bfs.bfs_greedy(XYPoint(2,3), XYPoint(9,3));
}

vector<XYPoint> run_astar() {
	Grid grid(10,5);
	ShortestPath bfs(&grid);

	grid.setWeight(4,1,3);
	grid.setWeight(4,2,3);
	grid.setWeight(4,3,3);
	grid.setWeight(5,1,9);
	grid.setWeight(5,2,9);
	grid.setWeight(5,3,9);
	grid.setWeight(6,1,3);
	grid.setWeight(6,2,3);
	grid.setWeight(6,3,3);

	return bfs.bfs_astar(XYPoint(2,3), XYPoint(9,3));
}

int main() {

	cout << "Hello World" << endl;
	cout << "\033[1;31mbold red text\033[0m\n";

//	run_bfs_w_early_exit();


	//auto path = run_astar();
	//auto path = run_dijkstra();
	auto path = run_greedy();

	if(!path.empty()) {
		cout << "GOAL!! ";
		for(auto p : path)  {
			cout << p << ' ';
		}
		cout << endl;
	}

//	Screen scr;
//
//	for(int i=0; i<10; i++) {
//		XYPoint p(i,0);
//		scr.set(p.getX(), p.getY(), 'X', Screen::COL_MNT, A_UNDERLINE);
//	}
//	getch();


	return 0;
}
