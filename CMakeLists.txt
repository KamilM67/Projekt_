cmake_minimum_required(Version 3.10)
project(TowerDefense)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "C:/sfml/SFML-2.6.2/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
set(SOURCES
    main.cpp
    GameManager.cpp
    Enemy.cpp
    Tower.cpp
    Projectile.cpp

)
set(HEADERS
    Config.h
    Enemy.h
    GameObject.h
    GameManager.h
    Projectile.h
    Tower.h
)
