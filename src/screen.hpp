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

/*! \brief A screen to present information to the user.
 *
 * A Screen object is used to display information on the screen or in a terminal. It
 * implements a screen buffer that stores all modifications that are written by its
 * update method to the screen.
 */
class Screen {
	unsigned int *buffer;
	unsigned int height;
	unsigned int width;
	bool tty;
public:
	/*! \brief Constructs a screen object with the given height and width.
	 */
	Screen(unsigned int h, unsigned int w);
	/*! \brief Disposes the screen.
	 */
	~Screen();

	/*! \brief Sets a formatted character at a certain position on the screen.
	 *
	 * @param[in] x		The X coordinate for character c on the screen
	 * @param[in] y		The Y coordinate for character c on the screen
	 * @param[in] c		Character to display
	 * @param[in] col   Color formatting as a ncurses color pair
	 * @param[in] att   Additional formatting options such as underline. Use 0 as default.
	 */
	void set(int x, int y, char c, unsigned int col, unsigned int att);

	/*! \brief Writes the screen buffer to the output device.
	 */
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
