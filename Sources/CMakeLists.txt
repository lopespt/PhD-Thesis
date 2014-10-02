

#Add ComplexNetwork dir to build ComplexNetwork lib
ADD_SUBDIRECTORY(ComplexNetwork)
ADD_SUBDIRECTORY(FeatureExtractors)

#Add required packages to build all others executables
#FIND_PACKAGE(Qt5Widgets REQUIRED)
#FIND_PACKAGE(OpenCV REQUIRED)

#Set include directory to the root "include" dir
INCLUDE_DIRECTORIES(${CMAKE_INCLUDE_OUTPUT_DIRECTORY})


ADD_SUBDIRECTORY(Utilities)

FILE(GLOB_RECURSE Utilities_SRC
    ${PhDThesis_SOURCE_DIR}/Sources/Utilities/*.cpp)
FILE(GLOB_RECURSE FeatureExtractors_SRC
    ${PhDThesis_SOURCE_DIR}/Sources/FeatureExtractors/*.cpp)
FILE(GLOB_RECURSE ComplexNetwork_SRC
    ${PhDThesis_SOURCE_DIR}/Sources/ComplexNetwork/*.cpp)


ADD_SUBDIRECTORY(Tests)

