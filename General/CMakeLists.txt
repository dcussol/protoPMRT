#version minimum requise de CMake
cmake_minimum_required(VERSION 2.6)

#Declaration du module
set(module PMRTGeneral)

#Utilisation du CMake general
include(../PMRTLists.cmake)

#directory des include
include_directories(
        ./
        ../DataTypes/
        ../Utilitaires/
)
