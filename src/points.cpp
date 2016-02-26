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

bool Point2D::issmaller(Point2D p) const {
	return tie( x, p.y ) < tie( p.x, y );
}

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

WeightedPoint2D Grid::getWeightedPoint(Point2D pp) {
	for(auto p : points) {
		if(p==pp) {
			return p;
		}
	}
	return WeightedPoint2D(pp,0);
}

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

//	if(y-1>=0) {
//		n.push_back(Point2D(x,y-1));
//	}
//	if(x-1>=0) {
//		n.push_back(Point2D(x-1,y));
//	}
//	if(y+1<g.getHeight()) {
//		n.push_back(Point2D(x,y+1));
//	}
//	if(x+1<g.getWidth()) {
//		n.push_back(Point2D(x+1,y));
//	}

	return n;
}





