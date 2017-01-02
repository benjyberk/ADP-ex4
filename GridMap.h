//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#ifndef ADVANCED_EX2_GRIDMAP_H
#define ADVANCED_EX2_GRIDMAP_H


#include <queue>
#include <cstdlib>
#include "GraphSquare.h"
#include "Point.h"

/**
 * The GridMap class holds, in this case, an NxN 2d array of GraphSquares. The GraphSquares are
 * used for the BFS routing algorithm, thus methods for finding neighbours and accessing the
 * nodes are required.
 * The getNeighbours and getNode methods can be overriden by inheritors to cover more dimensions
 * than simple 2d.  For dimensions larger than the provided grid allows for, inherited classes
 * would need to provide a replacement container.
 */
class GridMap {
protected:
    int maxHeight;
    int maxWidth;
    // Initialized on construction
    std::vector<Point> obstacles;
public:
    GraphSquare* grid[10][10];
    // The constructor method takes in the size required
    GridMap(int width, int height, std::vector<Point>);
    // Returns between 2-4 neighbours of a given point
    virtual std::vector<GraphSquare *> getNeighbours(Point);
    // Returns the pointer to the GraphSquare at a given x/y coordinate
    virtual GraphSquare * getNode(Point);
    // The destructor loops through the 2d array, deleting all elements.
    void reset();
    ~GridMap();
};


#endif //ADVANCED_EX2_GRIDMAP_H
