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
	unsigned int *buffer;
	unsigned int height;
	unsigned int width;
public:
	Screen(unsigned int h, unsigned int w);
	~Screen();
	void set(int x, int y, char c, unsigned int col, unsigned int att);
	//void set(XYPoint p, char c, unsigned int col, unsigned int att);
	void update();

	enum palette {
		COL_FLAT = 9,
		COL_MNT,
		COL_MNT_P,
		COL_CLEAR,
		COL_F1
	};
};



#endif /* SCREEN_HPP_ */
