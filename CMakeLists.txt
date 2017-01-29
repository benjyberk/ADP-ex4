cmake_minimum_required(VERSION 3.6)
project(ADP_ex4)

message(STATUS "start running cmake...")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES DriverTaxiClasses/Driver.cpp DriverTaxiClasses/Driver.h DriverTaxiClasses/MaritalStatus.h DriverTaxiClasses/Color.h MapClasses/Point.cpp MapClasses/Point.h MapClasses/GraphSquare.cpp MapClasses/GraphSquare.h MapClasses/GridMap.cpp MapClasses/GridMap.h MapClasses/FindPath.cpp MapClasses/FindPath.h DriverTaxiClasses/TripInfo.cpp DriverTaxiClasses/TripInfo.h DriverTaxiClasses/Passenger.cpp DriverTaxiClasses/Passenger.h DriverTaxiClasses/Taxi.cpp DriverTaxiClasses/Taxi.h DriverTaxiClasses/CarMaker.h DriverTaxiClasses/StandardTaxi.cpp DriverTaxiClasses/StandardTaxi.h DriverTaxiClasses/LuxuryTaxi.cpp DriverTaxiClasses/LuxuryTaxi.h DriverTaxiClasses/TaxiDispatch.cpp DriverTaxiClasses/TaxiDispatch.h DriverTaxiClasses/DriverLocationListener.cpp DriverTaxiClasses/DriverLocationListener.h GameControlClasses/GameControl.cpp GameControlClasses/GameControl.h DriverTaxiClasses/DriverTaxiContainer.cpp DriverTaxiClasses/DriverTaxiContainer.h GameControlClasses/Serializer.cpp GameControlClasses/Serializer.h DriverTaxiClasses/Clock.cpp DriverTaxiClasses/Clock.h StructuralClasses/Socket.cpp StructuralClasses/Socket.h StructuralClasses/Udp.cpp StructuralClasses/Udp.h StructuralClasses/Tcp.cpp StructuralClasses/Tcp.h StructuralClasses/ThreadPool.cpp StructuralClasses/ThreadPool.h StructuralClasses/Task.cpp StructuralClasses/Task.h)
set(MAIN_FILES_SERVER MainClasses/server.cpp)
set(MAIN_FILES_CLIENT MainClasses/client.cpp)
add_executable(ADP_ex4_server ${MAIN_FILES_SERVER} ${SOURCE_FILES})
add_executable(ADP_ex4_client ${MAIN_FILES_CLIENT} ${SOURCE_FILES})
target_link_libraries(ADP_ex4_server pthread)
target_link_libraries(ADP_ex4_client pthread)
