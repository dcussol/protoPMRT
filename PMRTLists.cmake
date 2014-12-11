#message de construction
message(
	"---> Creation du module ${BoldGreen}${module}${ColourReset}"
)

# Utilisation de <random> et <chrono>
SET( CMAKE_CXX_FLAGS "-std=c++0x")

#Generation de la liste des fichiers sources
file(
        GLOB_RECURSE
        source_files
        *.C
)

#Generation de la liste des fichiers include
file(
        GLOB_RECURSE
        include_files
        *.h
)

add_library(
        ${module}
        SHARED
        ${source_files}
        ${include_files}
)

#directory des include
include_directories(
        ./
)

#directory d'installation
#install (TARGETS ${module} DESTINATION ${install_dir}/libs)
#install (FILES ${include_files} DESTINATION ${install_dir}/include)

# intallation de la librairie
add_custom_target(install${module} ALL)
add_custom_command(
	 DEPENDS lib${module}.so
	 COMMAND mkdir
	 ARGS	 -p ${install_dir}/libs/
	 COMMAND cp
	 ARGS	 lib${module}.so ${install_dir}/libs/
	 COMMAND mkdir
	 ARGS	 -p ${install_dir}/include/
	 COMMAND cp
	 ARGS	 ${include_files} ${install_dir}/include/
	 TARGET  install${module}
)

add_dependencies(install${module} ${module})
