//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include "Point.h"

using namespace std;

Point::Point(int setX, int setY) {
    x = setX;
    y = setY;
}

Point::Point() {
    // Default construction into points -1 and -1
    x = -1;
    y = -1;
}

/**
 * Takes a point with x and y members and turns it into the string (x,y)
 */
string Point::toString() {
    stringstream returnString;
    returnString << "(" << x << "," << y << ")";
    return returnString.str();
}

/**
 * Compares two points on their x and y values, if they are equal true is returned, else false.
 */
bool Point::operator==(Point& other) {
    return ((x == other.x) && (y == other.y));
}

int Point::distanceTo(Point) {
    return 0;
}
