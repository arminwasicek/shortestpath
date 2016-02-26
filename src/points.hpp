/*
 * points.hpp
 *
 *  Created on: Feb 19, 2016
 *      Author: armin
 */

#ifndef POINTS_HPP_
#define POINTS_HPP_

#include <vector>
#include <iostream>
#include <iomanip>

#include "screen.hpp"

using namespace std;

class Grid;

class Point2D {
protected:
	int x;
	int y;
public:
	Point2D() { x=0; y=0; }
	Point2D(int x, int y);
	bool equals(int x, int y) const;
	bool equals(Point2D p) const;
	bool issmaller(Point2D p) const;
	int dist(Point2D a, unsigned int type);
	int getX() const {return x;};
	int getY() const {return y;};
	vector<Point2D> neighbours(Grid g);

	enum disttype {
		MANHATTEN = 0,
		EUCLID
	};
};


class WeightedPoint2D : public Point2D {
	int w;
public:
	WeightedPoint2D(Point2D p, int w);
	WeightedPoint2D(int x, int y, int w);
	int getWeight();
	bool issmaller(WeightedPoint2D p) const;

	struct compare
	{
	  bool operator()(const WeightedPoint2D& l, const WeightedPoint2D& r)
	  {
	      return !l.issmaller(r);
	  }
	};
};


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

inline bool operator<(const Point2D& lhs, const Point2D& rhs) {
	return lhs.issmaller(rhs);
}
inline bool operator==(const Point2D& lhs, const Point2D& rhs) {
	return lhs.equals(rhs);
}
inline bool operator!=(const Point2D& lhs, const Point2D& rhs){
	return !(lhs == rhs);
}
inline ostream& operator<<(ostream& out, const Point2D& p) {
   return out << '(' << p.getX() << ',' << p.getY() << ')';
}

inline bool operator<(const WeightedPoint2D& lhs, const WeightedPoint2D& rhs) {
	return lhs.issmaller(rhs);
}
inline bool operator>(const WeightedPoint2D& lhs, const WeightedPoint2D& rhs) {
	return !lhs.issmaller(rhs);
}



#endif /* POINTS_HPP_ */
