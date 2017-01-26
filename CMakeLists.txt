cmake_minimum_required(VERSION 3.6)
project(ADP_ex4)

message(STATUS "start running cmake...")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Driver.cpp Driver.h MaritalStatus.h Color.h Point.cpp Point.h GraphSquare.cpp GraphSquare.h GridMap.cpp GridMap.h findPath.cpp findPath.h TripInfo.cpp TripInfo.h Passenger.cpp Passenger.h Taxi.cpp Taxi.h CarMaker.h StandardTaxi.cpp StandardTaxi.h LuxuryTaxi.cpp LuxuryTaxi.h TaxiDispatch.cpp TaxiDispatch.h DriverLocationListener.cpp DriverLocationListener.h GameControl.cpp GameControl.h DriverTaxiContainer.cpp DriverTaxiContainer.h Serializer.cpp Serializer.h Clock.cpp Clock.h Socket.cpp Socket.h Udp.cpp Udp.h Tcp.cpp Tcp.h ThreadPool.cpp ThreadPool.h Task.cpp Task.h)
set(MAIN_FILES_SERVER server.cpp ThreadPool.cpp ThreadPool.h Task.cpp Task.h)
set(MAIN_FILES_CLIENT client.cpp ThreadPool.cpp ThreadPool.h Task.cpp Task.h)
add_executable(ADP_ex4_server ${MAIN_FILES_SERVER} ${SOURCE_FILES})
add_executable(ADP_ex4_client ${MAIN_FILES_CLIENT} ${SOURCE_FILES})
target_link_libraries(ADP_ex4_server pthread)
target_link_libraries(ADP_ex4_client pthread)
