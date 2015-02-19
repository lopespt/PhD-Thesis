#Create FeatureExtractors library
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)

FILE(GLOB_RECURSE Source_Files
    DatabaseReader.cpp
    SunDatabaseReader.cpp
    SupervisedImage.cpp
    ComplexNetworkConstructor/*.cpp
    DatabaseReader/*.cpp
    FeaturesComplexNetwork.cpp
    Link.cpp
    GraphUtilities.cpp
    IterativeRandomWalk.cpp
    KFoldDatabaseReader.cpp
    Utils.cpp
)
ADD_LIBRARY(Utilities ${Source_Files})
TARGET_LINK_LIBRARIES(Utilities FeatureExtractors ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${OpenCV_LIBRARIES} ${LEMON_LIBRARIES} ComplexNetwork)



#Copy header files to root include dir
FILE(GLOB_RECURSE header_files ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
add_custom_command(
    TARGET Utilities 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
    ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/Utilities  
    COMMAND cp -f ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
    ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/Utilities/
)
