cmake_minimum_required(VERSION 3.17)

project(woc_client_tests LANGUAGES C CXX)



set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)## Always include the current directory

find_package(OpenSSL 3.1 REQUIRED)
if (OPENSSL_FOUND)
    message(STATUS, "OPENSSL Version -> ${OPENSSL_VERSION}")
    message(STATUS, "OPENSSL INC DiR -> ${OPENSSL_INCLUDE_DIR}")
    message(STATUS, "OPENSSL LIBRARY -> ${OPENSSL_LIBRARIES}")
endif()

find_package(CURL REQUIRED)
if (CURL_FOUND)
    message(STATUS, "CURL VERSION -> ${CURL_VERSION_STRING}")
    message(STATUS, "CURL LIBRARIES -> ${CURL_LIBRARIES}")
    message(STATUS, "CURL INC DIR -> ${CURL_INCLUDE_DIR}")
endif()

find_package(cpprestsdk CONFIG REQUIRED)
if (cpprestsdk_FOUND)
    message(STATUS, "FOUND cpprestsdk")
endif()

set(woc_client_hdrs
    "${CMAKE_CURRENT_SOURCE_DIR}/include/woc.h")

set(woc_client_cc
    "${CMAKE_CURRENT_SOURCE_DIR}/src/woc.cc")

add_library(woc_client_lib SHARED ${woc_client_hdrs} ${woc_client_cc})
target_link_libraries(woc_client_lib OpenSSL::Crypto cpprestsdk::cpprest)

add_executable(WoC_Client ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc)
target_include_directories(WoC_Client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(WoC_Client PRIVATE woc_client_lib OpenSSL::Crypto cpprestsdk::cpprest)