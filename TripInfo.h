//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#ifndef ADVANCED_EX2_TRIPINFO_H
#define ADVANCED_EX2_TRIPINFO_H


#include <stack>
#include <vector>
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
    std::vector<Point>* route;
public:
    TripInfo(int, Point, Point, int, int, int);
    TripInfo();
    int getStartTime();
    void updateMeter(int);
    void changeEndPoint(Point);
    int getNumPassengers();
    int getTarrif();
    void assignRoute(std::vector<Point>*);
    std::vector<Point>* getRoute();
    int getRideID();
    int getCurrentDistance();

    virtual ~TripInfo();

    Point getStartPoint();
    Point getEndPoint();
};


#endif //ADVANCED_EX2_TRIPINFO_H
