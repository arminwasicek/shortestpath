/*
 * grid.hpp
 *
 *  Created on: Feb 25, 2016
 *      Author: armin
 */

#ifndef GRID_HPP_
#define GRID_HPP_

#include <vector>
#include "points.hpp"

class Point2D;
class WeightedPoint2D;

using namespace std;

class Grid {
	vector<WeightedPoint2D> points;
	int height;
	int width;
public:
	Grid(int w,	int h) { height=h; width=w; }
	bool inside(Point2D p);
	int getCost(Point2D a, Point2D b);
	//void plot();
	void plotw(Screen *scr);
	WeightedPoint2D getWeightedPoint(Point2D p);
	void setWeight(int x, int y, int w);
	void setWeight(Point2D p, int w);
	int getWeight(int x, int y);
	int getWeight(Point2D p);
	int getHeight()  { return height; }
	int getWidth()  { return width; }
};





#endif /* GRID_HPP_ */
