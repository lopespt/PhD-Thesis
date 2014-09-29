 #clean-all.cmake
FILE(GLOB_RECURSE cmake_generated  CMakeFiles/*)
#FILE(GLOB_RECURSE cmake_generated ./*/CMakeCache.txt)
#FILE(GLOB_RECURSE cmake_generated ./*/cmake_install.cmake)
#FILE(GLOB_RECURSE cmake_generated ./*/Makefile)
#FILE(GLOB_RECURSE cmake_generated ./bin)
#FILE(GLOB_RECURSE cmake_generated ./lib)
MACRO(SUBDIRLIST result curdir regex)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    MESSAGE(STATUS Entrei)
    FOREACH(child ${children})
        MESSAGE(STATUS Analisando ${child})
        IF(IS_DIRECTORY ${curdir}/${child} AND child MATCHES
                ${regex} )
            MESSAGE(STATUS bateu ${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()


SUBDIRLIST(res ./ *)

foreach(file ${cmake_generated})
    #MESSAGE(STATUS Cleaning ${file})
    if(EXISTS ${file})
        file(REMOVE_RECURSE ${file})
    endif()

endforeach(file)


