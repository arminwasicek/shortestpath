/*
 * points.cpp
 *
 *  Created on: Feb 19, 2016
 *      Author: armin
 */


#include "points.hpp"

/* =========================================    */

XYPoint::XYPoint(int xx, int yy) {
	x=xx; y=yy;
}

bool XYPoint::equals(int xx, int yy) const {
	return equals(XYPoint(xx,yy));
}

bool XYPoint::equals(XYPoint p) const {
	if((p.x==x) && (p.y==y))  {
		return true;
	}
	return false;
}

bool XYPoint::issmaller(XYPoint p) const {
	if((p.x<x) || (p.y<y))  {
		return true;
	}
	return false;
}

/* =========================================    */

WeightedXYPoint::WeightedXYPoint(XYPoint p, int ww)  {
	x=p.getX();
	y=p.getY();
	w=ww;
}

WeightedXYPoint::WeightedXYPoint(int xx, int yy, int ww)  {
	x=xx;
	y=yy;
	w=ww;
}

int WeightedXYPoint::getWeight() {
	return w;
}


/* =========================================    */


void Grid::setWeight(int x, int y, int w) {
	points.push_back(WeightedXYPoint(x,y,w));
}

void Grid::setWeight(XYPoint p, int w) {
	points.push_back(WeightedXYPoint(p,w));
}



int Grid::getWeight(int x, int y) {
	vector<WeightedXYPoint>::iterator it;

	for(it=points.begin(); it!=points.end(); ++it) {
		WeightedXYPoint p = *it;
		if(p.equals(x,y))
			return p.getWeight();
	}

	return 0;
}

int Grid::getWeight(XYPoint p) {
	return getWeight(p.getX(), p.getY());
}


void Grid::plot() {
	for(int i=0; i<height; i++) {
		for(int j=0; j<width; j++) {
				int w = getWeight(j,i);
				if(w<1)
					cout << " . ";
				else
					cout << setfill(' ') << setw(3) << w;
		}
		cout << endl;
	}
}


vector<XYPoint> XYPoint::neighbours(Grid g) {
	vector<XYPoint> n;

	if(y-1>=0) {
		n.push_back(XYPoint(x,y-1));
	}
	if(x-1>=0) {
		n.push_back(XYPoint(x-1,y));
	}
	if(y+1<g.getHeight()) {
		n.push_back(XYPoint(x,y+1));
	}
	if(x+1<g.getWidth()) {
		n.push_back(XYPoint(x+1,y));
	}

	return n;
}



