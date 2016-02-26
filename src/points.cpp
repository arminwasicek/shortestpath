/*
 * points.cpp
 *
 *  Created on: Feb 19, 2016
 *      Author: armin
 */


#include "points.hpp"

/* =========================================    */

Point2D::Point2D(int xx, int yy) {
	x=xx; y=yy;
}

bool Point2D::equals(int xx, int yy) const {
	return equals(Point2D(xx,yy));
}

bool Point2D::equals(Point2D p) const {
	if((p.x==x) && (p.y==y))  {
		return true;
	}
	return false;
}

/*!
 * \note Implements the strict weak ordering required for the map.
 */
bool Point2D::issmaller(Point2D p) const {
	return tie( x, p.y ) < tie( p.x, y );
}

/*!
 * \note Currently, only the Manhatten distance is implemented.
 */
int Point2D::dist(Point2D a, unsigned int type) {
	switch(type) {
		case Point2D::MANHATTEN :
			return abs(x-a.getX()) + abs(y-a.getY());
		case Point2D::EUCLID :
		default:
			return 0;
	}
}

bool WeightedPoint2D::issmaller(WeightedPoint2D p) const {
	if(w<p.w) {
		return true;
	}
	if(w==p.w) {
		return tie( x, p.y ) < tie( p.x, y );
	}
	return false;
}


/* =========================================    */

WeightedPoint2D::WeightedPoint2D(Point2D p, int ww)  {
	x=p.getX();
	y=p.getY();
	w=ww;
}

WeightedPoint2D::WeightedPoint2D(int xx, int yy, int ww)  {
	x=xx;
	y=yy;
	w=ww;
}

int WeightedPoint2D::getWeight() {
	return w;
}

/*!
 * \note Searches linearly in the point vector.
 * \todo Replace vector datastructure with tree-based method, e.g., kd-tree or grid file.
 */
WeightedPoint2D Grid::getWeightedPoint(Point2D pp) {
	for(auto p : points) {
		if(p==pp) {
			return p;
		}
	}
	return WeightedPoint2D(pp,0);
}

/*!
 * \note Returns North, West, South, East adjacent points as neighbours.
 * \todo Parameterize method to facilitate for different neighbour computations.
 */
vector<Point2D> Point2D::neighbours(Grid g) {
	vector<Point2D> n;
	int relx[] = {0, -1, 0, 1};
	int rely[] = {-1, 0, 1, 0};

	for(int i=0; i<4; i++) {
		Point2D p = Point2D(x+relx[i],y+rely[i]);
		if(g.inside(p)) {
			if(g.getWeight(p)<MAXWEIGHT) {
				n.push_back(p);
			}
		}
	}
	return n;
}





