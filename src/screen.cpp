/*
 * screen.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: armin
 */


#include "screen.hpp"


Screen::Screen()  {
	if(isatty(fileno(stdout)))  {
		cout << "is a tty :)" << endl;
	}
    initscr();                 /* Start curses mode     */
    noecho();
}

Screen::~Screen()  {
    endwin();
}


void Screen::set(int x, int y, char c, unsigned int att) {
	unsigned int ch = c | att;
	mvwaddch(stdscr, y, x, ch);
	refresh();
}

