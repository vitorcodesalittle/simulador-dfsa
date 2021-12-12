cmake_minimum_required(VERSION 3.19)
project(simulador)
set(CMAKE_CXX_STANDARD 17)
add_executable(simulador)
target_sources(
        simulador
        PRIVATE
            src/main.cpp
            src/config.cpp
            src/config.h
            src/Simulador.cpp
            src/Simulador.h
            src/Estimator.cpp
            src/Estimator.h
)