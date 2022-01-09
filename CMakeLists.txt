cmake_minimum_required(VERSION 3.21)
project(advisorbot)

set(CMAKE_CXX_STANDARD 11)

add_executable(advisorbot main.cpp AdvisorMain.cpp AdvisorMain.h CSVReader.cpp CSVReader.h OrderBook.cpp OrderBook.h OrderBookEntry.cpp OrderBookEntry.h Calculator.cpp Calculator.h)
