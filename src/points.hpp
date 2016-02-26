/*
 * points.hpp
 *
 *  Created on: Feb 19, 2016
 *      Author: armin
 */

#ifndef POINTS_HPP_
#define POINTS_HPP_

#include <vector>
#include <iostream>
#include <iomanip>

#include "screen.hpp"
#include "grid.hpp"

using namespace std;

/*! A forward reference to the Grid class. */
class Grid;


/*! \brief The Point2D class defines the data structure for representing a point.
 *
 *  A point in 2D space has an X and a Y coordinate. A point is a geometric primitive
 *  and allows several operations to compare and measure distances. With respect to a
 *  grid, neighbours and other notions can be established.
 */
class Point2D {
protected:
	int x;
	int y;
public:
	/*! \brief Constructs a point in 2D space at the origin.
	 *
	 */
	Point2D() { x=0; y=0; }

	/*! \brief Constructs a point in 2D space with the given X and Y coordinates.
	 *
	 * @param[in]  x  	The X coordinate of the 2D point
	 * @param[in]  y    The Y coordinate of the 2D point
	 */
	Point2D(int x, int y);

	/*! \brief Computes the neighbors of the point object w.r.t to a grid.
	 *
	 * @param[in]  g  The grid that the point object belongs to.
	 * \return The neighbouring points on the given grid.
	 */
	vector<Point2D> neighbours(Grid g);

	/*! \brief Tests for equality between two points.
	 *
	 * @param[in]  x  The point's X coordinate
	 * @param[in]  y  The point's Y coordinate
	 * \return True, if equal
	 */
	bool equals(int x, int y) const;

	/*! \brief Tests for equality between two points.
	 *
	 * @param[in]  p  The point's coordinates
	 * \return True, if equal
	 */
	bool equals(Point2D p) const;

	/*! \brief Tests, if the object is smaller than the point in the argument.
	 *
	 * @param[in]  p  The coordinates of the point to compare to
	 * \return True, if smaller
	 */
	bool issmaller(Point2D p) const;

	/*! \brief Computes the distance between two points.
	 *
	 * @param[in]  p  	The coordinates of the distant point
	 * @param[in]  type The method used for comparison (Manhatten, Euclid)
	 * \return The distance between both points
	 */
	int dist(Point2D a, unsigned int type);

	/*! \brief Gets the point's X coordinate.
	 *
	 * \return The point's X coordinate
	 */
	int getX() const {return x;};

	/*! \brief Gets the point's Y coordinate.
	 *
	 * \return The point's Y coordinate
	 */
	int getY() const {return y;};

	/*! \brief Enumeration for the different distance functions available.
	 */
	enum disttype {
		/**  Manhatten distance: abs(x-x') + abs(y-y')*/
		MANHATTEN = 0,
		/**  Euclidian distance: sqrt( (x-x')^2 + (y-y')^2 ) */
		EUCLID
	};
};

/*! \brief The WeightedPoint2D class improves the Point2D class by adding a notion of
 * 		   weight to points.
 *
 *  A weighted point in 2D space has an X and a Y coordinate, as well as a weight. The
 *  weight can be used to refine the geometric primitive and can be interpreted for example
 *  as elevation, terrain type, etc.
 */
class WeightedPoint2D : public Point2D {
	int w;
public:
	/*! \brief Constructs a point in 2D space given a Point2D object.
	 */
	WeightedPoint2D(Point2D p, int w);

	/*! \brief Constructs a point in 2D space given X and Y coordinates and a weight.
	 */
	WeightedPoint2D(int x, int y, int w);

	/*! \brief Gets the point's weight.
	 *
	 * \return The point's weight
	 */
	int getWeight();

	/*! \brief Tests, if the object is smaller than the point in the argument.
	 *
	 * @param[in]  p  The coordinates of the point to compare to
	 * \return True, if smaller
	 */
	bool issmaller(WeightedPoint2D p) const;

	/*! \brief Tests, if the lefthand side point object is bigger than the righthand side one.
	 *
	 * This operator is primarily used to establish the strict weak ordering required to order
	 * the elements in a priority queue.
	 *
	 */
	struct compare
	{
	  bool operator()(const WeightedPoint2D& l, const WeightedPoint2D& r)
	  {
	      return !l.issmaller(r);
	  }
	};
};




inline bool operator<(const Point2D& lhs, const Point2D& rhs) {
	return lhs.issmaller(rhs);
}
inline bool operator==(const Point2D& lhs, const Point2D& rhs) {
	return lhs.equals(rhs);
}
inline bool operator!=(const Point2D& lhs, const Point2D& rhs){
	return !(lhs == rhs);
}
inline ostream& operator<<(ostream& out, const Point2D& p) {
   return out << '(' << p.getX() << ',' << p.getY() << ')';
}
inline bool operator<(const WeightedPoint2D& lhs, const WeightedPoint2D& rhs) {
	return lhs.issmaller(rhs);
}
inline bool operator>(const WeightedPoint2D& lhs, const WeightedPoint2D& rhs) {
	return !lhs.issmaller(rhs);
}



#endif /* POINTS_HPP_ */
