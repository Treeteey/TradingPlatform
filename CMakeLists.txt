cmake_minimum_required(VERSION 3.20)
project(TradingEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(orderbook STATIC src/lock_free_order_book.cpp)

# подключаем зависимости через Conan
find_package(GTest REQUIRED)
target_link_libraries(orderbook PRIVATE Gtest::Gtest)
