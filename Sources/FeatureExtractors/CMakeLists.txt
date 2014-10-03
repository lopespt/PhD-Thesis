#Create FeatureExtractors library
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)


FILE(GLOB_RECURSE Source_Files  *.cpp)
ADD_LIBRARY(FeatureExtractors ${Source_Files})
TARGET_LINK_LIBRARIES(FeatureExtractors ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES})



#Copy header files to root include dir
FILE(GLOB_RECURSE header_files ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
add_custom_command(
    TARGET FeatureExtractors 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/FeatureExtractors  
    COMMAND cp -f ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/FeatureExtractors/
)
