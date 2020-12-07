get_property(result CACHE QTNOTE_VERSION PROPERTY TYPE)
if ("${result}" STREQUAL "")
    if (EXISTS "${CMAKE_SOURCE_DIR}/.git")
        find_package(Git)
        if (Git_FOUND)
            execute_process(COMMAND ${GIT_EXECUTABLE} -C "${CMAKE_SOURCE_DIR}" describe --tags --always
                            OUTPUT_VARIABLE GIT_REPO_VERSION)
            string(STRIP "${GIT_REPO_VERSION}" GIT_REPO_VERSION)
            string(REGEX REPLACE "\.0-" "." GIT_REPO_VERSION ${GIT_REPO_VERSION})
            string(REGEX REPLACE "-.*" "" GIT_REPO_VERSION ${GIT_REPO_VERSION})
            set(QTNOTE_VERSION ${GIT_REPO_VERSION} CACHE STRING "QtNote version string")
        endif()
    else()
        file(READ "${CMAKE_SOURCE_DIR}/version" QTNOTE_VERSION_FILE)
        set(QTNOTE_VERSION ${QTNOTE_VERSION_FILE} CACHE STRING "QtNote version string")
    endif()

    if ("${QTNOTE_VERSION}" STREQUAL "")
        message(WARNING "Failed to find QtNote version. Using 0.0.0")
        set(QTNOTE_VERSION "0.0.0" CACHE STRING "QtNote version string")
    endif()
endif()

macro(add_qtnote_plugin name description)
    cmake_minimum_required(VERSION 3.10.0)
    project(qtnote_plugin_${name} VERSION ${QTNOTE_VERSION} LANGUAGES CXX)
    option(QTNOTE_ENABLE_${name} "Enable QtNote plugin: ${description}")
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
    set(QTNOTE_COMMON_PLUGIN_SRC
        ${plugins_SOURCE_DIR}/deintegrationinterface.h
        ${plugins_SOURCE_DIR}/qtnoteplugininterface.h
        ${plugins_SOURCE_DIR}/trayimpl.h
        )
endmacro()