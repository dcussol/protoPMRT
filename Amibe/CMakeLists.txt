#version minimum requise de CMake
cmake_minimum_required(VERSION 2.6)

#Declaration du projet
project(AmibeTest)

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
set(source_files TestAmibe.C)
set(source_proba_files TestProbaAmibe.C)

#Generation de la liste des fichiers include
file(
        GLOB_RECURSE
        include_files
        *.h
)

#liste des modules a ajouter
set(modules Imagerie Irradiation Biologie Traducteur PhysiqueMedicale Medical)

#liste des includes
set(include_dirs "")
foreach(module ${modules})
 set(include_dirs ${include_dirs} ${module})
endforeach()

#liste des librairies
set(lib_files "")
foreach(module ${modules})
 set(lib_files ${lib_files} ${install_dir}/libs/libAmibe${module}.so)
endforeach()



#directory des include
include_directories(
        ./
	${install_dir}/include/
	${include_dirs}
)

add_executable(
        TestAmibe
	${source_files}
	${include_files}
)

add_executable(
        TestProbaAmibe
	${source_proba_files}
	${include_files}
)

#liens des librairies
target_link_libraries(
        TestAmibe
        ${install_dir}/libs/libPMRTGeneral.so
        ${install_dir}/libs/libPMRTDataTypes.so
        ${install_dir}/libs/libPMRTUtilitaires.so
        ${lib_files}
)

target_link_libraries(
        TestProbaAmibe
        ${install_dir}/libs/libPMRTGeneral.so
        ${install_dir}/libs/libPMRTDataTypes.so
        ${install_dir}/libs/libPMRTUtilitaires.so
        ${lib_files}
)

# Sous repertoires du AmibeModel
foreach(module ${modules})
 add_subdirectory(${module}) 
endforeach()

#dependances des cibles
set(depencies "")
foreach(module ${modules})
 set(depencies ${depencies} installAmibe${module})
endforeach()

add_dependencies(TestAmibe
	${depencies}
)
add_dependencies(TestProbaAmibe
	${depencies}
)

# Fichiers pour la tarball
set(tar_files "../Amibe/Imagerie/*.[C,h]")
#set(tar_files ${tar_files} ../Amibe/Irradiation/*.[C,h])
#set(tar_files ${tar_files} ../Amibe/Biologie/*.[C,h])
#set(tar_files ${tar_files} ../Amibe/Medical/*.[C,h])
#set(tar_files ${tar_files} ../Amibe/PhysiqueMedicale/*.[C,h]) 
#set(tar_files ${tar_files} ../Amibe/Traducteur/*.[C,h])
set(tar_files ${tar_files} ../Amibe/*/CMakeLists.txt)
set(tar_files ${tar_files} ../Amibe/CMakeLists.txt)
set(tar_files ${tar_files} ../Amibe/AmibeLists.cmake)
#set(tar_files ${tar_files} ../Amibe/VisiteurAmibe.[C,h])
#set(tar_files ${tar_files} ../Amibe/PrintAmibe.[C,h])
#set(tar_files ${tar_files} ../Amibe/SuiviCartographieAmibe.[C,h])
#set(tar_files ${tar_files} ../Amibe/TestAmibe.[C,h])
#set(tar_files ${tar_files} ../Amibe/TestProbaAmibe.[C,h])
#set(tar_files ${tar_files} ../Amibe/ManuelTestAmibe.txt)
#set(tar_files ${tar_files} ../Amibe/README)

add_custom_target(tarball)
add_custom_command(
	COMMAND tar
	ARGS    -cvzf AmibeModel.tgz ${tar_files}
	TARGET  tarball
)

