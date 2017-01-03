cmake_minimum_required(VERSION 3.6)
project(ADP_ex4)

message(STATUS "start running cmake...")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(Boost 1.58 COMPONENTS serialization iostreams REQUIRED)
if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")


    include_directories(${Boost_INCLUDE_DIRS})
endif()
set(SOURCE_FILES Driver.cpp Driver.h MaritalStatus.h Color.h Point.cpp Point.h GraphSquare.cpp GraphSquare.h GridMap.cpp GridMap.h findPath.cpp findPath.h TripInfo.cpp TripInfo.h Passenger.cpp Passenger.h Taxi.cpp Taxi.h CarMaker.h StandardTaxi.cpp StandardTaxi.h LuxuryTaxi.cpp LuxuryTaxi.h TaxiDispatch.cpp TaxiDispatch.h DriverLocationListener.cpp DriverLocationListener.h GameControl.cpp GameControl.h DriverTaxiContainer.cpp DriverTaxiContainer.h Serializer.cpp Serializer.h)
set(MAIN_FILES main.cpp Clock.cpp Clock.h client.cpp client.h)
add_executable(ADP_ex4 ${MAIN_FILES} ${SOURCE_FILES})
target_link_libraries(ADP_ex4 ${Boost_LIBRARIES})
