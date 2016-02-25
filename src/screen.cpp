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
    start_color();
    noecho();

    init_color(COL_FLAT, 200, 680, 680);
    init_color(COL_MNT, 20, 680, 0);
    init_pair(COL_MNT, COLOR_BLACK, COL_MNT);
    init_pair(COL_FLAT, COLOR_BLACK, COL_FLAT);
    init_pair(COL_MNT_P, COLOR_BLUE, COL_MNT);
    init_pair(COL_CLEAR, COLOR_WHITE, COLOR_BLACK);
    init_pair(COL_F1, COLOR_GREEN, COL_MNT);
}

Screen::~Screen()  {
    endwin();
}


void Screen::set(int x, int y, char c, unsigned int col, unsigned int att) {
	unsigned int ch = c | COLOR_PAIR(col) | att;
	mvwaddch(stdscr, y, x, ch);
	refresh();
}

//void Screen::set(XYPoint p, char c, unsigned int col, unsigned int att) {
//	set(p.getX(), p.getY(), c, col, att);
//}

void Screen::update() {
	refresh();
}
