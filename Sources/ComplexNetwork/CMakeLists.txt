
#Create ComplexNetwork library
#FIND_PACKAGE(Armadillo)
FILE(GLOB_RECURSE Source_Files  *.cpp *.hpp)
ADD_LIBRARY(ComplexNetwork ${Source_Files})
#TARGET_LINK_LIBRARIES(ComplexNetwork Armadillo)

#Copy header files to root include dir
FILE(GLOB_RECURSE header_files ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
add_custom_command(
    TARGET ComplexNetwork 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/ComplexNetwork  
    COMMAND cp -f ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/ComplexNetwork/
)
