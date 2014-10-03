
FIND_PACKAGE(OpenCV REQUIRED)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)


FILE(GLOB_RECURSE Source_Files  *.cpp)

ADD_LIBRARY(Segmentation ${Source_Files})
TARGET_LINK_LIBRARIES(Segmentation ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${OpenCV_LIBRARIES})


#Copy header files to root include dir
FILE(GLOB_RECURSE header_files ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
add_custom_command(
    TARGET Segmentation 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
    ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/Segmentation  
    COMMAND cp -f ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
    ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/Segmentation/
)
