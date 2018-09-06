cmake_minimum_required ( VERSION 3.1 )
set (PROJECT_NAME AllegroExt)

project(${PROJECT_NAME})

set(CMAKE_BUILD_TYPE "Release" CACHE STRING "")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_GENERATOR_PLATFORM x64)

set(allegincludedir "" CACHE STRING "The directory of allegro includes")
set(alleglibdir "" CACHE STRING "The directories of allegro's libraries")
set(alleglib "liballegro" CACHE STRING "The path of the main allegro library relative to allegdir")
set(ttflib "liballegro_ttf" CACHE STRING "The path of the ttf allegro extension relative to allegdir")
set(imglib "liballegro_image" CACHE STRING "The path of the img allegro extension relative to allegdir")
set(primlib "liballegro_primitives" CACHE STRING "The path of the primtive allegro extension relative to allegdir")
set(fontlib "liballegro_font" CACHE STRING "The path of the font allegro extension relative to allegdir")

set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/allegroext)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(HEADERS
	${HEADER_DIR}/Button.h
    ${HEADER_DIR}/Core.h
    ${HEADER_DIR}/DefaultLoadSign.h
    ${HEADER_DIR}/DisplayManager.h
    ${HEADER_DIR}/FPSLogger.h
    ${HEADER_DIR}/Image.h
    ${HEADER_DIR}/InputManager.h
    ${HEADER_DIR}/LoadSign.h
    ${HEADER_DIR}/MLScreenText.h
    ${HEADER_DIR}/Music.h
    ${HEADER_DIR}/ScreenText.h
    ${HEADER_DIR}/ShapeRenderer.h
    ${HEADER_DIR}/SoundEffect.h
    ${HEADER_DIR}/TextField.h)

set(SOURCES
	${SOURCE_DIR}/Button.cpp
    ${SOURCE_DIR}/Core.cpp
    ${SOURCE_DIR}/DefaultLoadSign.cpp
    ${SOURCE_DIR}/FPSLogger.cpp
    ${SOURCE_DIR}/Image.cpp
    ${SOURCE_DIR}/InputManager.cpp
    ${SOURCE_DIR}/LoadSign.cpp
    ${SOURCE_DIR}/MLScreenText.cpp
    ${SOURCE_DIR}/Music.cpp
    ${SOURCE_DIR}/ScreenText.cpp
    ${SOURCE_DIR}/ShapeRenderer.cpp
    ${SOURCE_DIR}/SoundEffect.cpp
    ${SOURCE_DIR}/SoundManager.cpp
    ${SOURCE_DIR}/TextField.cpp)

include_directories(
    ${HEADER_DIR})

include_directories(
    ${allegincludedir})

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
    ${alleglibdir}${alleglib}
    ${alleglibdir}${ttflib}
    ${alleglibdir}${imglib}
    ${alleglibdir}${primlib}
    ${alleglibdir}${fontlib})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED 11)