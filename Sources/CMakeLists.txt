

ADD_SUBDIRECTORY(ComplexNetwork)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)


INCLUDE_DIRECTORIES(${PhDThesis_SOURCE_DIR}/Sources/ComplexNetwork/
    ${PhDThesis_SOURCE_DIR}/Sources/FeatureExtractors/
    ${PhDThesis_SOURCE_DIR}/Sources/Utilities/)


FILE(GLOB_RECURSE Utilities_SRC
    ${PhDThesis_SOURCE_DIR}/Sources/Utilities/*.cpp)
FILE(GLOB_RECURSE FeatureExtractors_SRC
    ${PhDThesis_SOURCE_DIR}/Sources/FeatureExtractors/*.cpp)
FILE(GLOB_RECURSE ComplexNetwork_SRC
    ${PhDThesis_SOURCE_DIR}/Sources/ComplexNetwork/*.cpp)


ADD_SUBDIRECTORY(Tests)

