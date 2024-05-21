cmake_minimum_required(VERSION 3.25)

project(
        MediaKeysFix
        VERSION 1.0.1
        LANGUAGES CXX)
set(PROJECT_LICENSE "LGPLv3")
set(PROJECT_COPYRIGHT "Copyright (c) 2023 Emerson Pinter")
set(PROJECT_FRIENDLY_NAME ${PROJECT_NAME})
set(PROJECT_LONG_NAME "Media Keys Fix")
set(PROJECT_DESCRIPTION ${PROJECT_LONG_NAME})

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(GNUInstallDirs)
include(addpluginsources)
include(pluginconfig)

######## dependencies
find_package(CommonLibSSE REQUIRED)
add_commonlibsse_plugin(${PROJECT_NAME} SOURCES ${HEADER_FILES} ${SOURCE_FILES}
                        NAME ${PROJECT_NAME}
                        AUTHOR "Emerson Pinter"
                        VERSION ${PROJECT_VERSION}
                        )
target_include_directories(${PROJECT_NAME} PRIVATE ${SIMPLEINI_INCLUDE_DIRS})

######## target
add_library("${PROJECT_NAME}::${PROJECT_NAME}" ALIAS "${PROJECT_NAME}")

target_include_directories(${PROJECT_NAME}
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src>
        $<INSTALL_INTERFACE:src>)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/PCH.h")
    target_precompile_headers(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PCH.h")
endif()

######## install and distribution
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "SKSE/Plugins")

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/dist/${PROJECT_NAME}.ini"
        DESTINATION "SKSE/Plugins")

set(CPACK_GENERATOR 7Z)
set(CPACK_PACKAGE_NAME ${PROJECT_LONG_NAME})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CMAKE_PROJECT_VERSION}")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)
include(CPack)
