cmake_minimum_required(VERSION 3.1.0)

project(civet LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Qml Quick Gui Multimedia Network REQUIRED)

set(
  SOURCES
  src/cpp/main.cpp
  src/cpp/MouseClient.cpp
  src/cpp/KeyboardClient.cpp
  src/cpp/CursorMove.cpp
)

add_executable(
  civet
  ${SOURCES}
  src/qml.qrc
 )

target_link_libraries(civet Qt5::Qml Qt5::Quick Qt5::Multimedia Qt5::Network)
