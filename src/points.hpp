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

using namespace std;

class Grid;

class XYPoint {
protected:
	int x;
	int y;
public:
	XYPoint() { x=0; y=0; }
	XYPoint(int x, int y);
	bool equals(int x, int y) const;
	bool equals(XYPoint p) const;
	bool issmaller(XYPoint p) const;
	int getX() const {return x;};
	int getY() const {return y;};
	vector<XYPoint> neighbours(Grid g);
};


class WeightedXYPoint : public XYPoint {
	int w;
public:
	WeightedXYPoint(XYPoint p, int w);
	WeightedXYPoint(int x, int y, int w);
	int getWeight();
	bool issmaller(WeightedXYPoint p) const;

	struct compare
	{
	  bool operator()(const WeightedXYPoint& l, const WeightedXYPoint& r)
	  {
	      return !l.issmaller(r);
	  }
	};
};


class Grid {
	vector<WeightedXYPoint> points;
	int height;
	int width;
public:
	Grid(int w,	int h) { height=h; width=w; }
	int getWeight(int x, int y);
	int getWeight(XYPoint p);
	int getCost(XYPoint a, XYPoint b);
	WeightedXYPoint getWeightedPoint(XYPoint p);
	void setWeight(int x, int y, int w);
	void setWeight(XYPoint p, int w);
	void plot();
	void plotw();
	int getHeight()  { return height; }
	int getWidth()  { return width; }
	bool inside(XYPoint p);
};

inline bool operator<(const XYPoint& lhs, const XYPoint& rhs) {
	return lhs.issmaller(rhs);
}
inline bool operator==(const XYPoint& lhs, const XYPoint& rhs) {
	return lhs.equals(rhs);
}
inline bool operator!=(const XYPoint& lhs, const XYPoint& rhs){
	return !(lhs == rhs);
}
inline ostream& operator<<(ostream& out, const XYPoint& p) {
   return out << '(' << p.getX() << ',' << p.getY() << ')';
}

inline bool operator<(const WeightedXYPoint& lhs, const WeightedXYPoint& rhs) {
	return lhs.issmaller(rhs);
}
inline bool operator>(const WeightedXYPoint& lhs, const WeightedXYPoint& rhs) {
	return !lhs.issmaller(rhs);
}



#endif /* POINTS_HPP_ */
