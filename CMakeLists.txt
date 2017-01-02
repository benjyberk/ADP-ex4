cmake_minimum_required(VERSION 3.6)
project(ADP_ex4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Driver.cpp Driver.h MaritalStatus.h Color.h Point.cpp Point.h GraphSquare.cpp GraphSquare.h GridMap.cpp GridMap.h findPath.cpp findPath.h TripInfo.cpp TripInfo.h Passenger.cpp Passenger.h Taxi.cpp Taxi.h CarMaker.h StandardTaxi.cpp StandardTaxi.h LuxuryTaxi.cpp LuxuryTaxi.h TaxiDispatch.cpp TaxiDispatch.h DriverLocationListener.cpp DriverLocationListener.h GameControl.cpp GameControl.h DriverTaxiContainer.cpp DriverTaxiContainer.h)
set(MAIN_FILES main.cpp Clock.cpp Clock.h)
add_executable(ADP_ex4 ${MAIN_FILES} ${SOURCE_FILES})