//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#ifndef ADVANCED_EX2_GRAPHSQUARE_H
#define ADVANCED_EX2_GRAPHSQUARE_H


#include "Point.h"

/**
 * A GraphSquare is simply a point with the extra information of 'distance from source' and
 * 'predecessor', this allows the GraphSqaure to become the main components of the gridmap used to
 * perform bfs.
 */
class GraphSquare {
public:
    Point* gridLocation;
    int distanceFromSource;
    Point* predecessor;
    // Can be constructed either with a provided or not provided Point object
    GraphSquare(Point*);
    // If no Point is provided, one is initialized in this constructor
    GraphSquare();
    // The destructor frees the contained Point object.
    ~GraphSquare();
    bool operator ==(GraphSquare other);
};

#endif //ADVANCED_EX2_GRAPHSQUARE_H
