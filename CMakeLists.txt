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

add_executable(TowerDefense ${SOURCES} ${HEADERS}
    Menu.cpp
    Menu.h)

target_link_libraries(TowerDefense sfml-graphics sfml-window sfml-system)
if(WIN32)
    add_custom_command(TARGET TowerDefense POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SFML_DIR}/../../../bin/sfml-graphics-2.dll"
        "${SFML_DIR}/../../../bin/sfml-window-2.dll"
        "${SFML_DIR}/../../../bin/sfml-system-2.dll"
        $<TARGET_FILE_DIR:TowerDefense>)
endif()
add_custom_command(TARGET TowerDefense POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/arial.ttf"
    $<TARGET_FILE_DIR:TowerDefense>)



