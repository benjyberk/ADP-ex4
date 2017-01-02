//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include "GridMap.h"
#include <algorithm>

using namespace std;

/**
 * Initializes the 2d array to a given size
 * @param width width of the array
 * @param height height of the array
 */
GridMap::GridMap(int width, int height, vector<Point> inputObstacles) {
    obstacles = inputObstacles;
    maxWidth = width;
    maxHeight = height;
    // The array is constructed such that the point 0,0 is at [0][height-1]
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Point* tempPoint = new Point(i, height - j - 1);
            GraphSquare* tempGraphSquare = new GraphSquare(tempPoint);
            tempGraphSquare->distanceFromSource = -1;
            grid[i][height - j - 1] = tempGraphSquare;
        }
    }
}

/**
 * The function searches for neighbours of a given point, checking essentially if the point is at
 * a corner, and if so skipping that neighbour.
 * @param xpos the x position of the node
 * @param ypos the y position of the node
 */
vector<GraphSquare *> GridMap::getNeighbours(Point find) {
    std::vector<Point>::iterator finder;
    int xpos = find.x;
    int ypos = find.y;

    // An array of the neighbours to be created is initialized
    vector<GraphSquare *> adjacent;

    // Each check makes sure that the neighbour to be added actually exists
    if ((xpos - 1) > -1) {
        adjacent.push_back(grid[xpos - 1][ypos]);
    }
    if ((ypos + 1) < maxHeight) {
        adjacent.push_back(grid[xpos][ypos + 1]);
    }
    if ((xpos + 1) < maxWidth) {
        adjacent.push_back(grid[xpos + 1][ypos]);
    }
    if ((ypos - 1) > -1) {
        adjacent.push_back(grid[xpos][ypos - 1]);
    }

    for (int i = 0; i < adjacent.size(); i++) {
        int found = 0;
        for (int j = 0; j < obstacles.size(); j++) {

            Point a = *(adjacent[i]->gridLocation);
            Point b = obstacles[j];
            if (a == b) {
                found = 1;
                break;
            }
        }
        if (found) {
            adjacent.erase(adjacent.begin() + i);
        }
    }

    // The constructed array is returned
    return adjacent;
}

/**
 * Returns a GraphSquare at a specified point
 * @param xpos x position of the point
 * @param ypos y position of the point
 * @return the requested GraphSquare
 */
GraphSquare* GridMap::getNode(Point find) {
    return grid[find.x][find.y];
}

/**
 * The destructor loops through the 2d array, freeing all memory.
 */
GridMap::~GridMap() {
    for (int i = 0; i < maxWidth; i++) {
        for (int j = 0; j < maxHeight; j++) {
            delete grid[i][j];
        }
    }
}

void GridMap::reset() {
    for (int i = 0; i < maxWidth; i++) {
        for (int j = 0; j < maxHeight; j++) {
            grid[i][maxHeight - j - 1]->distanceFromSource = -1;
            grid[i][maxHeight - j - 1]->predecessor = 0;
        }
    }
}
