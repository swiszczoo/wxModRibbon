cmake_minimum_required(VERSION 3.21)
project(wxModRibbon)
include(FindPkgConfig.cmake)

option(WXMR_EXAMPLE "Compile wxModRibbon xample" OFF)
option(WXMR_SHARED "Build shared library" OFF)

set(WXW_USE_DEBUG OFF)
set(WXW_USE_UNICODE OFF)
set(WXW_USE_SHARED ON)
set(WXW_USE_UNIV OFF)
set(WXW_USE_MONO OFF)

set(WXW_FILE_VERSION "32")
set(WXW_VERSION "3.2")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})
add_definitions( ${WXWIDGETS_DEFINITIONS} )

set(WXBF_SHARED ${WXMR_SHARED})
cmake_policy(SET CMP0077 NEW)
add_subdirectory(wxBorderlessFrame)

set(LIB_SOURCES
    src/test.cpp
)

set(EXAMPLE_SOURCES example/main.cpp)

if(UNIX AND NOT APPLE)
    add_definitions( -DLINUX=1 )
    PKGCONFIG("gtk+-3.0")
    if(PKGCONFIG_FOUND)
        if(CMAKE_PKGCONFIG_C_FLAGS)
            set(CMAKE_CXX_FLAGS "${CMAKE_PKGCONFIG_C_FLAGS} ${CMAKE_CXX_FLAGS}")
            set(WXWIDGETS_LIBRARIES "${PKGCONFIG_LIBRARIES} ${WXWIDGETS_LIBRARIES}")
            #do something with ${PKGCONFIG_LIBRARIES}
        endif(CMAKE_PKGCONFIG_C_FLAGS)
    else(PKGCONFIG_FOUND)
        message("Cannot find gtk+-3.0")
    endif(PKGCONFIG_FOUND)
endif(UNIX AND NOT APPLE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}${WXWIDGETS_CXX_FLAGS}")

if(WXMR_SHARED)
    set(WXMR_LIBRARY_TYPE SHARED)
else()
    set(WXMR_LIBRARY_TYPE STATIC)
endif()

add_library(${PROJECT_NAME} ${WXMR_LIBRARY_TYPE} ${LIB_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include PRIVATE ${wxWidgets_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${wxWidgets_LINK_DIRECTORIES})
target_link_libraries(${PROJECT_NAME} PUBLIC wxBorderlessFrame)
target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES})

if(WXMR_EXAMPLE)
    add_executable(example WIN32 ${EXAMPLE_SOURCES})
    target_link_libraries(example PUBLIC ${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES})
    add_custom_command(TARGET example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:example> $<TARGET_FILE_DIR:example>
        COMMAND_EXPAND_LISTS
        )
endif()
