
all: server client

# Put here all the common files which are being used both in client and server
COMMON_SOURCES = Driver.cpp Driver.h MaritalStatus.h Color.h Point.cpp Point.h GraphSquare.cpp GraphSquare.h GridMap.cpp GridMap.h findPath.cpp findPath.h TripInfo.cpp TripInfo.h Passenger.cpp Passenger.h Taxi.cpp Taxi.h CarMaker.h StandardTaxi.cpp StandardTaxi.h LuxuryTaxi.cpp LuxuryTaxi.h TaxiDispatch.cpp TaxiDispatch.h DriverLocationListener.cpp DriverLocationListener.h GameControl.cpp GameControl.h DriverTaxiContainer.cpp DriverTaxiContainer.h Serializer.cpp Serializer.h Clock.cpp Clock.h Socket.cpp Socket.h Udp.cpp Udp.h Tcp.cpp Tcp.h

server:
	g++ -std=c++0x server.cpp $(COMMON_SOURCES) -I. -o server.out -lpthread
# (for example)
client:
	g++ -std=c++0x client.cpp $(COMMON_SOURCES) -I. -o client.out -lpthread
