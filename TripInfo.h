//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#ifndef ADVANCED_EX2_TRIPINFO_H
#define ADVANCED_EX2_TRIPINFO_H


#include <stack>
#include "Point.h"

class TripInfo {
private:
    int rideID;
    int currentDistance;
    Point startPoint;
    Point endPoint;
    int tarrif;
    int numPassengers;
    int startTime;
    std::stack<Point>* route;
public:
    TripInfo(int, Point, Point, int, int, int);
    TripInfo();
    int getStartTime();
    void updateMeter(int);
    void changeEndPoint(Point);
    void assignRoute(std::stack<Point>*);
    std::stack<Point>* getRoute();
    int getRideID();
    int getCurrentDistance();
    Point getStartPoint();
    Point getEndPoint();
};


#endif //ADVANCED_EX2_TRIPINFO_H
