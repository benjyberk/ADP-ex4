
all: server client

# Put here all the common files which are being used both in client and server
COMMON_SOURCES = DriverTaxiClasses/Driver.cpp DriverTaxiClasses/Driver.h DriverTaxiClasses/MaritalStatus.h DriverTaxiClasses/Color.h MapClasses/Point.cpp MapClasses/Point.h MapClasses/GraphSquare.cpp MapClasses/GraphSquare.h MapClasses/GridMap.cpp MapClasses/GridMap.h MapClasses/FindPath.cpp MapClasses/FindPath.h DriverTaxiClasses/TripInfo.cpp DriverTaxiClasses/TripInfo.h DriverTaxiClasses/Passenger.cpp DriverTaxiClasses/Passenger.h DriverTaxiClasses/Taxi.cpp DriverTaxiClasses/Taxi.h DriverTaxiClasses/CarMaker.h DriverTaxiClasses/StandardTaxi.cpp DriverTaxiClasses/StandardTaxi.h DriverTaxiClasses/LuxuryTaxi.cpp DriverTaxiClasses/LuxuryTaxi.h DriverTaxiClasses/TaxiDispatch.cpp DriverTaxiClasses/TaxiDispatch.h DriverTaxiClasses/DriverLocationListener.cpp DriverTaxiClasses/DriverLocationListener.h GameControlClasses/GameControl.cpp GameControlClasses/GameControl.h DriverTaxiClasses/DriverTaxiContainer.cpp DriverTaxiClasses/DriverTaxiContainer.h GameControlClasses/Serializer.cpp GameControlClasses/Serializer.h DriverTaxiClasses/Clock.cpp DriverTaxiClasses/Clock.h StructuralClasses/Socket.cpp StructuralClasses/Socket.h StructuralClasses/Udp.cpp StructuralClasses/Udp.h StructuralClasses/Tcp.cpp StructuralClasses/Tcp.h StructuralClasses/ThreadPool.cpp StructuralClasses/ThreadPool.h StructuralClasses/Task.cpp StructuralClasses/Task.h

server:
	g++ -std=c++0x MainClasses/server.cpp $(COMMON_SOURCES) -I. -o server.out -lpthread
# (for example)
client:
	g++ -std=c++0x MainClasses/client.cpp $(COMMON_SOURCES) -I. -o client.out -lpthread
