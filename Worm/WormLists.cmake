#Directory d'installation
#set (install_dir $ENV{PMRTDIR})

message(
	"---> Creation du module ${BoldGreen}${module}${ColourReset}"
)

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
	${install_dir}/include/
)

#directory d'installation
#install (TARGETS ${module} DESTINATION ${install_dir}/libs)

add_custom_target(install${module} ALL)
add_custom_command(
	 DEPENDS lib${module}.so
	 COMMAND cp
	 ARGS	 lib${module}.so ${install_dir}/libs/
	 TARGET  install${module}
)

add_dependencies(install${module} ${module})
