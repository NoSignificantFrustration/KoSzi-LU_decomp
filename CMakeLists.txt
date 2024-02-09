cmake_minimum_required(VERSION 3.10)
project(LU_Decomp)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

SET(BOOST_ROOT "~/boost_1_83_0/boost")
SET(BOOST_INCLUDEDIR "~/boost_1_83_0")
SET(BOOST_LIBRARYDIR "~/boost_1_83_0/stage/lib")

find_package(Boost 1.83 )

include_directories(${BOOST_INCLUDEDIR})

add_executable(LU_Decomp
 Main.cpp
 Matrix.h
 Fraction.h
 LU_Decomp.h
 Matrix.cpp
 Fraction.cpp
 LU_Decomp.cpp
 )


target_link_libraries(LU_Decomp LINK_PUBLIC ${BOOST_LIBRARYDIR}/libboost_chrono.so)



