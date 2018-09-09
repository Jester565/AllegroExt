cmake_minimum_required ( VERSION 3.1 )
set (AE_PROJECT_NAME AllegroExt)

project(${AE_PROJECT_NAME})

set(CMAKE_BUILD_TYPE "Release" CACHE STRING "")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} /MTd")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_GENERATOR_PLATFORM x64)

set(allegro false CACHE BOOL "Link to allegro")
if (allegro)
    set(allegincludedir "" CACHE STRING "The directory of allegro includes")
    set(alleglibdir "" CACHE STRING "The directories of allegro's libraries")
    if (UNIX)
        set(alleglib "liballegro.a" CACHE STRING "The path of the main allegro library relative to allegdir")
        set(ttflib "liballegro_ttf.a" CACHE STRING "The path of the ttf allegro extension relative to allegdir")
        set(imglib "liballegro_image.a" CACHE STRING "The path of the img allegro extension relative to allegdir")
        set(primlib "liballegro_primitives.a" CACHE STRING "The path of the primtive allegro extension relative to allegdir")
        set(fontlib "liballegro_font.a" CACHE STRING "The path of the font allegro extension relative to allegdir")
    else()
        set(alleglib "allegro-static.lib" CACHE STRING "The path of the main allegro library relative to allegdir")
        set(ttflib "allegro_ttf-static.lib" CACHE STRING "The path of the ttf allegro extension relative to allegdir")
        set(imglib "allegro_image-static.lib" CACHE STRING "The path of the img allegro extension relative to allegdir")
        set(primlib "allegro_primitives-static.lib" CACHE STRING "The path of the primtive allegro extension relative to allegdir")
        set(fontlib "allegro_font-static.lib" CACHE STRING "The path of the font allegro extension relative to allegdir")
    endif()
endif()

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
    ${SOURCE_DIR}/DisplayManager.cpp
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

add_library(${AE_PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_link_libraries(${AE_PROJECT_NAME}
    ${alleglibdir}${alleglib}
    ${alleglibdir}${ttflib}
    ${alleglibdir}${imglib}
    ${alleglibdir}${primlib}
    ${alleglibdir}${fontlib})

set_property(TARGET ${AE_PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${AE_PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED 11)