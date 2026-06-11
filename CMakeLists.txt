cmake_minimum_required(VERSION 3.16)

project(GitTowerDefense LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(GitTowerDefense main.cpp
    Enemy.h Enemy.cpp
    Config.h
    GameManager.h GameManager.cpp
    GameObject.h
    Menu.h Menu.cpp
    Projectile.h Projectile.cpp
    Tower.h Tower.cpp)

include(GNUInstallDirs)
install(TARGETS GitTowerDefense
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
