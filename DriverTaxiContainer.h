//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#ifndef EX2_V2_DRIVERTAXICONTAINER_H
#define EX2_V2_DRIVERTAXICONTAINER_H

class Taxi;

#include "Taxi.h"
#include "Socket.h"

/**
 * A container class that holds the driver and the taxi as well as their location
 */
class DriverTaxiContainer {
public:
    Taxi * taxi;
    Driver * driver;
    Point * location;
    Socket * socket;
    DriverTaxiContainer();
    void setDriver(Driver *);
    void setTaxi(Taxi *);
    void setSocket(Socket *);
    Socket *getSocket();
    Taxi *getTaxi();
    void setLocation(Point *);
    ~DriverTaxiContainer();
};


#endif //EX2_V2_DRIVERTAXICONTAINER_H
