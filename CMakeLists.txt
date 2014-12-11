#version minimum requise de CMake
cmake_minimum_required(VERSION 2.6)

#Declaration du projet
project(PMRTproto)

string(ASCII 27 Esc)
set(ColourReset "${Esc}[m")
set(BoldRed     "${Esc}[1;31m")
set(BoldGreen   "${Esc}[1;32m")

#Directory d'installation
set (install_dir $ENV{PMRTDIR})
if(NOT DEFINED install_dir)
 message("${BoldRed}Veuillez definir la variable d'environnement PMRTDIR.${ColourReset}")
 message(FATAL_ERROR "Arret de la procedure.")
endif()

# Sous repertoires du prototype de PMRT
add_subdirectory(DataTypes) 
add_subdirectory(Utilitaires) 
add_subdirectory(General) 

# cible vide pour appeler les intallations des differents modules
add_custom_target(PMRTproto ALL)

#dependances des cibles
add_dependencies(PMRTproto
	installPMRTDataTypes
        installPMRTUtilitaires
        installPMRTGeneral
)

# Fichiers pour la tarball
set(tar_files "DataTypes/*.[C,h]")
set(tar_files ${tar_files} DataTypes/CMakeLists.txt)
set(tar_files ${tar_files} Utilitaires/*.[C,h])
set(tar_files ${tar_files} Utilitaires/CMakeLists.txt)
set(tar_files ${tar_files} General/*.[C,h])
set(tar_files ${tar_files} General/CMakeLists.txt)
set(tar_files ${tar_files} ./PMRTLists.cmake)
set(tar_files ${tar_files} ./CMakeLists.txt)
set(tar_files ${tar_files} ./README)

add_custom_target(tarball)
add_custom_command(
	COMMAND tar
	ARGS    -cvzf PMRTproto.tgz ${tar_files}
	TARGET  tarball
)

