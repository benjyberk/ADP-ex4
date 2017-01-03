//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#ifndef ADP_EX4_SERIALIZER_H
#define ADP_EX4_SERIALIZER_H


#include "Driver.h"

class Serializer {
public:
    static std::string serializeDriver(Driver*);
    static Driver* deserializeDriver(std::string);
    static std::string serializeTaxi(Taxi*);
    static Taxi* deserializeTaxi(std::string);
    static std::string serializeTrip(TripInfo*);
    static TripInfo* deserializeTrip(std::string);
    static std::string serializePoint(Point);

};


#endif //ADP_EX4_SERIALIZER_H
