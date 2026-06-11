cmake_minimum_required(VERSION 3.16)

project(GitTowerDefense LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(GitTowerDefense main.cpp)

include(GNUInstallDirs)
install(TARGETS GitTowerDefense
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
