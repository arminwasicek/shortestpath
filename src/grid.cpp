/*
 * grid.cpp
 *
 *  Created on: Feb 25, 2016
 *      Author: armin
 */


#include "grid.hpp"

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


bool Grid::inside(Point2D p) {
	if(((p.getX()>0) && (p.getX()<width)) && ((p.getY()>0) && (p.getY()<height)) ) {
		return true;
	}
	return false;
}

/*!
 * If the file cannot be loaded the program exits with return value 1.
 */
int Grid::load(string file) {
	string line;
	ifstream in(file);

	// Check, if the file stream is ready
	if (!in) {
		// Print an error and exit
		cerr << "File " << file << " could not be opened for reading." << endl;
		return 1;
	}

	// Iterate line by line through the file
	while(!in.eof())  {
		in >> line;
		// Catch height and width
        if(line=="height") {
        	string sub;
        	in >> sub;
	        height=stoi(sub);
	    }
		if(line=="width") {
        	string sub;
        	in >> sub;
			width=stoi(sub);
		}
	    // Catch map
		if(line=="map") {
			getline(in, line);
			int row=0;
			while(getline(in, line)) {
				for(int col=0; col<line.length(); col++) {
					if(line.at(col)=='@') {
						setWeight(col, row, 999999);
					}
				}
				row++;
			}
		}
		// Ignore the rest
	}
	return 0;
}

