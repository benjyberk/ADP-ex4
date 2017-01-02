//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#ifndef ADVANCED_EX2_POINT_H
#define ADVANCED_EX2_POINT_H

#include <iostream>
#include <sstream>

/**
 * The Point class is a container holding x and y integer members.
 * In order to make the GridMap and BfsAlgorithm work with more parameters, the point class would
 * need to be inherited and abstractded (used as an Interface), in particular, it would need to
 * hold more than just x and y parameters (it would need as many dimensions as required).
 */
class Point {
public:
    int x;
    int y;
    // Initializes the point to a given x and y values.
    Point(int setX, int setY);
    // Initializes the point to a default -1,-1
    Point();
    // Converts the point into a string form (readability)
    virtual std::string toString();
    // Compares two points with one another
    virtual bool operator==(Point &other);
    int distanceTo(Point);
};

#endif //ADVANCED_EX2_POINT_H
