/*
 * screen.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: armin
 */


#include "screen.hpp"

/*!
 * \note The constructor checks, if a tty terminal is present.
 */
Screen::Screen(unsigned int h, unsigned int w)  {
	if(isatty(fileno(stdout)))  {
		cout << "is a tty :)" << endl;
		tty = true;
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
	else  {
		tty = false;
	}

    buffer = new unsigned int[w*h];
    height = h;
    width = w;
}

Screen::~Screen()  {
	free(buffer);
	if(tty) {
		endwin();
		cout << "Exiting ncurses" << endl;
	}
}

/*! In case a single character without formatting is given, the character inherits
 *  formatting from the current settings at the position.
 */
void Screen::set(int x, int y, char c, unsigned int col, unsigned int att) {
	unsigned int ch = c | COLOR_PAIR(col) | att;
	if((col==0) && (att==0)) {
		ch = c | (buffer[x+y*width] & 0xFFFFFF00);
	}
	buffer[x+y*width] = ch;
}

/*!
 * \note Currently, the screen tries to distinguish between tty terminal and non-tty
 * 		 output device. If there is a tty terminal, it uses ncurses, otherwise Screen
 * 		 tried to do a raw screen dump.
 */
void Screen::update() {
	if(tty) {
		for(int i=0; i<width; i++)  {
			for(int j=0; j<height; j++) {
				mvwaddch(stdscr, j, i, buffer[i+j*width]);
			}
		}
		refresh();
	}
	else {
		for(int i=0; i<width; i++)  {
			for(int j=0; j<height; j++) {
				char ch = buffer[i+j*width] & 0xFFFFFF00;
				cout << ch;
			}
			cout << endl;
		}
	}
}
