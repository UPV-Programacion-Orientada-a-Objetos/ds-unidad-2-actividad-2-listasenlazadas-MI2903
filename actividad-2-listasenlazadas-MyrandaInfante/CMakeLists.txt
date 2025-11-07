cmake_minimum_required(VERSION 3.10)
project(PRT7Decoder)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Buscar Doxygen
find_package(Doxygen)

# Archivos fuente
set(SOURCES
    src/main.cpp
    src/TramaLoad.cpp
    src/TramaMap.cpp
    src/RotorDeMapeo.cpp
    src/ListaDeCarga.cpp
    src/SerialPort.cpp
)

# Ejecutable
add_executable(PRT7Decoder ${SOURCES})

# Generar documentacion con Doxygen
if(DOXYGEN_FOUND)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/docs/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generando documentacion con Doxygen"
        VERBATIM
    )
endif()