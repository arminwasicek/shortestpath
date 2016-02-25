/*
 * screen.hpp
 *
 *  Created on: Feb 24, 2016
 *      Author: armin
 */

#ifndef SCREEN_HPP_
#define SCREEN_HPP_

#include <ncurses.h>
#include <iostream>

//#include "points.hpp"

using namespace std;

class Screen {
public:
	Screen();
	~Screen();
	void set(int x, int y, char c, unsigned int col, unsigned int att);
	//void set(XYPoint p, char c, unsigned int col, unsigned int att);

	enum palette {
		COL_FLAT = 9,
		COL_MNT
	};
};



#endif /* SCREEN_HPP_ */
