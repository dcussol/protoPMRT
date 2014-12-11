#version minimum requise de CMake
cmake_minimum_required(VERSION 2.6)

#Declaration du projet
project(WormTest)

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

# Utilisation de <random> et <chrono>
SET( CMAKE_CXX_FLAGS "-std=c++0x")

#Generation de la liste des fichiers sources
set(source_files TestWorm.C VisiteurWorm.C PrintWorm.C SuiviCartographieWorm.C)

#Generation de la liste des fichiers include
file(
        GLOB_RECURSE
        include_files
        *.h
)


#directory des include
include_directories(
        ./
	${install_dir}/include/
	../Worm/Imagerie/
	../Worm/Irradiation/
	../Worm/Biologie/
	../Worm/Medical/
	../Worm/PhysiqueMedicale/
	../Worm/Traducteur/
)

add_executable(
        TestWorm
	${source_files}
	${include_files}
)
#liens des librairies
target_link_libraries(
        TestWorm
        ${install_dir}/libs/libPMRTGeneral.so
        ${install_dir}/libs/libPMRTDataTypes.so
        ${install_dir}/libs/libPMRTUtilitaires.so
        ${install_dir}/libs/libWormImagerie.so
        ${install_dir}/libs/libWormIrradiation.so
        ${install_dir}/libs/libWormBiologie.so
        ${install_dir}/libs/libWormMedical.so
        ${install_dir}/libs/libWormPhysiqueMedicale.so
        ${install_dir}/libs/libWormTraducteur.so
)

# Sous repertoires du WormModel
add_subdirectory(Imagerie) 
add_subdirectory(Irradiation) 
add_subdirectory(Biologie) 
add_subdirectory(Medical) 
add_subdirectory(PhysiqueMedicale) 
add_subdirectory(Traducteur) 

#dependances des cibles
add_dependencies(TestWorm
	installWormImagerie
        installWormIrradiation
        installWormBiologie
        installWormMedical
        installWormPhysiqueMedicale
        installWormTraducteur
)

# Fichiers pour la tarball
set(tar_files "../Worm/Imagerie/*.[C,h]")
set(tar_files ${tar_files} ../Worm/Irradiation/*.[C,h])
set(tar_files ${tar_files} ../Worm/Biologie/*.[C,h])
set(tar_files ${tar_files} ../Worm/Medical/*.[C,h])
set(tar_files ${tar_files} ../Worm/PhysiqueMedicale/*.[C,h]) 
set(tar_files ${tar_files} ../Worm/Traducteur/*.[C,h])
set(tar_files ${tar_files} ../Worm/*/CMakeLists.txt)
set(tar_files ${tar_files} ../Worm/CMakeLists.txt)
set(tar_files ${tar_files} ../Worm/WormLists.cmake)
set(tar_files ${tar_files} ../Worm/VisiteurWorm.[C,h])
set(tar_files ${tar_files} ../Worm/PrintWorm.[C,h])
set(tar_files ${tar_files} ../Worm/SuiviCartographieWorm.[C,h])
set(tar_files ${tar_files} ../Worm/TestWorm.[C,h])
set(tar_files ${tar_files} ../Worm/ManuelTestWorm.txt)
set(tar_files ${tar_files} ../Worm/README)

add_custom_target(tarball)
add_custom_command(
	COMMAND tar
	ARGS    -cvzf WormModel.tgz ${tar_files}
	TARGET  tarball
)

