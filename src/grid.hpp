/*
 * grid.hpp
 *
 *  Created on: Feb 25, 2016
 *      Author: armin
 */

/*! \file */

#ifndef GRID_HPP_
#define GRID_HPP_

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "points.hpp"

using namespace std;

/*! Forward declaration of a point. */
class Point2D;
/*! Forward declaration of a point with weight. */
class WeightedPoint2D;

/*! Cap the weight. All values beyond this value are treated as solid. */
#define MAXWEIGHT  1000

/*! \brief The grid defines the data structure for the graph.
 *
 *  A grid is a set of weighted points. Weights can represent elevations,
 *  vegetation zones, etc. A weight value beyond the defined maximum makes
 *  the point a solid. Points without a weight are interpreted as plains.
 */
class Grid {

	vector<WeightedPoint2D> points;				/**< Set of weighted points */
	int height;									/**< Height of the grid */
	int width;									/**< Width of the grid */

public:

	/*! \brief Constructs an empty grid.
	 *
	 */
	Grid() { height=0; width=0; };

	/*! \brief Constructs a grid with width and height.
	 *
	 * @param[in]  w  	The width for the grid
	 * @param[in]  h    The height for the grid
	 */
	Grid(int w,	int h) { height=h; width=w; }

	/*! \brief Tests, if a point is inside the grid.
	 *
	 * @param[in]  p  	The point to be tested
	 */
	bool inside(Point2D p);

	/*! \brief Computes the moving cost between two points.
	 *
	 * @param[in]  p  	The point to be tested
	 * \return True, if point p is inside
	 */
	int getCost(Point2D a, Point2D b);

	/*! \brief Loads a map from a file.
	 *
	 * @param[in]  file  The filename
	 * \return Status of the operation.
	 */
	int load(string file);

	/*! \brief Plots the grid on the screen.
	 *
	 * @param[in]  scr  A reference to a screen object
	 * \return 	Nothing
	 */
	void plotw(Screen *scr);

	/*! \brief Returns the weight of a point.
	 *
	 * @param[in]  p  The point's coordinates
	 * \return The point's weight
	 */
	WeightedPoint2D getWeightedPoint(Point2D p);

	/*! \brief Sets the point's weight.
	 *
	 * @param[in]  x  The point's X coordinate
	 * @param[in]  y  The point's Y coordinate
	 * @param[in]  w  The point's weight
	 * \return Nothing
	 */
	void setWeight(int x, int y, int w);

	/*! \brief Sets the point's weight.
	 *
	 * @param[in]  p  The point's coordinates
	 * @param[in]  w  The point's weight
	 * \return Nothing
	 */
	void setWeight(Point2D p, int w);

	/*! \brief Gets the point's weight.
	 *
	 * @param[in]  x  The point's X coordinate
	 * @param[in]  y  The point's Y coordinate
	 * \return The point's weight
	 */
	int getWeight(int x, int y);

	/*! \brief Gets the point's weight.
	 *
	 * @param[in]  p  The point's coordinates
	 * \return The point's weight
	 */
	int getWeight(Point2D p);

	/*! \brief Gets the grid's height.
	 *
	 * \return The point's height
	 */
	int getHeight()  { return height; }

	/*! \brief Gets the grid's width.
	 *
	 * \return The point's width
	 */
	int getWidth()  { return width; }
};





#endif /* GRID_HPP_ */
