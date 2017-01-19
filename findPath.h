//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#ifndef ADVANCED_EX2_BFSLOGIC_H
#define ADVANCED_EX2_BFSLOGIC_H

#include <stack>
#include <queue>
#include <vector>
#include <pthread.h>
#include "GridMap.h"

/**
 * The bfsLogic class, given a generic gridmap, maps out a route from a destination to the end
 * point.  Note, that any type of GridMap would work, as generic operators are used to find
 * the neighbours of any given point.  However the GridMap MUST be comprised of gridsquare (or
 * any inheritor that also contains the necessary fields).LL
 */
class findPath {
private:
    std::vector<Point *> cleanup;
public:
    /**
     * Given a generic GridMap, route a path from the source point to the destination point and
     * print it out.
     * @param search the Grid to search
     * @param source the source point
     * @param destination the destination point
     * @param lock the lock for multiple threads
     */
    std::vector<Point>* bfsRoute(GridMap* search, Point source,
                                 Point destination);

    virtual ~findPath();
};


#endif //ADVANCED_EX2_BFSLOGIC_H
