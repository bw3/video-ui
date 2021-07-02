include_directories(${Qt5Widgets_INCLUDE_DIRS} ${QtQml_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS} ${QtQml_DEFINITIONS} ${${Qt5Quick_DEFINITIONS}})
qt5_add_resources(QT_RESOURCES qml.qrc)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(PROJECT "video-ui")
project(${PROJECT})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -fstrict-aliasing -pedantic-errors -pedantic -Wno-deprecated-declarations -Wno-unused-variable")
set(HEADERS "backend.h" "menu_option.h" "video_options.h")
set(SOURCES "main.cpp" "backend.cpp" "menu_option.cpp" "video_options.cpp")
source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})
add_executable(${PROJECT} ${HEADERS} ${SOURCES} ${QT_RESOURCES})
target_link_libraries(${PROJECT}
    Qt5::Widgets
    Qt5::Qml
    Qt5::Quick
    mediainfo
    dl
    mpv
    )
