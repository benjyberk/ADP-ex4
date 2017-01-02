//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include "GraphSquare.h"

GraphSquare::GraphSquare(Point* gridSpot) {
    // The distanceFromSource is initialized to -1
    gridLocation = gridSpot;
    distanceFromSource = -1;
    predecessor = new Point(-1,-1);
}

GraphSquare::GraphSquare() {
    // The default values are initialized to -1, and a new Point is provided
    distanceFromSource = -1;
    gridLocation = new Point(-1,-1);
    predecessor = new Point(-1,-1);
}

GraphSquare::~GraphSquare() {
    delete gridLocation;
    delete predecessor;
}

bool GraphSquare::operator ==(GraphSquare other) {
    return *gridLocation == *other.gridLocation;
}
