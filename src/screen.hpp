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

using namespace std;

class Screen {
public:
	Screen();
	~Screen();
	void set(int x, int y, char c, unsigned int att);
};



#endif /* SCREEN_HPP_ */
