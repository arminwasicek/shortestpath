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

/* =========================================    */


void Grid::setWeight(int x, int y, int w) {
	points.push_back(WeightedPoint2D(x,y,w));
}

void Grid::setWeight(Point2D p, int w) {
	points.push_back(WeightedPoint2D(p,w));
}



int Grid::getWeight(int x, int y) {
	for(auto p : points) {
		if(p.equals(x,y))
			return p.getWeight();
	}

	return 0;
}

int Grid::getWeight(Point2D p) {
	return getWeight(p.getX(), p.getY());
}

int Grid::getCost(Point2D a, Point2D b) {
	int d = getWeight(b)-getWeight(a);
	if(d<=0) {
		d = 0;
	}
	d += abs(a.getX()-b.getX()) + abs(a.getY()-b.getY());
	return d;
}


void Grid::plotw(Screen *scr) {
	for(int i=0; i<width; i++) {
		for(int j=0; j<height; j++) {
			int w = getWeight(i,j);

			if(w==0) {
				scr->set(i, j, ' ', Screen::COL_MNT, 0);
			}
			else {
				char c = '0' + (char)(w % 10);
				scr->set(i, j, c, Screen::COL_FLAT, 0);
			}
		}
	}

}


vector<Point2D> Point2D::neighbours(Grid g) {
	vector<Point2D> n;

	if(y-1>=0) {
		n.push_back(Point2D(x,y-1));
	}
	if(x-1>=0) {
		n.push_back(Point2D(x-1,y));
	}
	if(y+1<g.getHeight()) {
		n.push_back(Point2D(x,y+1));
	}
	if(x+1<g.getWidth()) {
		n.push_back(Point2D(x+1,y));
	}

	return n;
}

bool Grid::inside(Point2D p) {
	if(((p.getX()>0) && (p.getX()<width)) && ((p.getY()>0) && (p.getY()<height)) ) {
		return true;
	}
	return false;
}



