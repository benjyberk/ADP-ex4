OBJS = Driver.cpp Point.cpp GraphSquare.cpp GridMap.cpp findPath.cpp TripInfo.cpp Passenger.cpp Taxi.cpp StandardTaxi.cpp LuxuryTaxi.cpp TaxiDispatch.cpp DriverLocationListener.cpp GameControl.cpp main.cpp DriverTaxiContainer.cpp
DEPS = Driver.h MaritalStatus.h Color.h Point.h GraphSquare.h GridMap.h findPath.h TripInfo.h Passenger.h Taxi.h CarMaker.h StandardTaxi.h LuxuryTaxi.h TaxiDispatch.h DriverLocationListener.h GameControl.h DriverTaxiContainer.h
a.out: Driver.cpp Point.cpp GraphSquare.cpp GridMap.cpp findPath.cpp TripInfo.cpp Passenger.cpp Taxi.cpp StandardTaxi.cpp LuxuryTaxi.cpp TaxiDispatch.cpp DriverLocationListener.cpp GameControl.cpp main.cpp DriverTaxiContainer.cpp
	g++ Driver.cpp Point.cpp GraphSquare.cpp GridMap.cpp findPath.cpp TripInfo.cpp Passenger.cpp Taxi.cpp StandardTaxi.cpp LuxuryTaxi.cpp TaxiDispatch.cpp DriverLocationListener.cpp GameControl.cpp main.cpp DriverTaxiContainer.cpp -o a.out
%.o: %.cpp $(DEPS)
	g++ -c %.cpp
clean:
	\rm *.o *~ a.out
