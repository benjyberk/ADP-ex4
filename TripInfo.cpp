//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include "TripInfo.h"

using namespace std;

TripInfo::TripInfo(int r_id, Point r_sPoint, Point r_dPoint, int r_numPass, int r_tar, int sTime) {
    rideID = r_id;
    startPoint = r_sPoint;
    endPoint = r_dPoint;
    numPassengers = r_numPass;
    tarrif = r_tar;
    startTime = sTime;
}

TripInfo::TripInfo() {
    rideID = 0;
    startPoint = Point();
    endPoint = Point();
    numPassengers = 0;
    tarrif = 0;
    startTime = -1;
}


void TripInfo::updateMeter(int) {

}

void TripInfo::changeEndPoint(Point) {

}

int TripInfo::getRideID() {
    return rideID;
}

int TripInfo::getCurrentDistance() {
    return 0;
}

Point TripInfo::getStartPoint() {
    return startPoint;
}

Point TripInfo::getEndPoint() {
    return endPoint;
}

void TripInfo::assignRoute(std::stack<Point>* assignedRoute) {
    route = assignedRoute;
}

std::stack<Point>* TripInfo::getRoute() {
    return route;
}

int TripInfo::getStartTime() {
    return startTime;
}

