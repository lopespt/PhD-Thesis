
#FIND_PACKAGE(Qt5Core REQUIRED)
#FIND_PACKAGE(Qt5OpenGL REQUIRED)
#FIND_PACKAGE(Qt5Widgets REQUIRED)
#FIND_PACKAGE(Qt5Sql REQUIRED)
#FIND_PACKAGE(Qt5WebKitWidgets REQUIRED)

INCLUDE_DIRECTORIES(".")
INCLUDE_DIRECTORIES("../../../")

FILE(GLOB_RECURSE Source_Files  *.cpp *.hpp)

ADD_EXECUTABLE(ComplexNetworkCompare ${Source_Files})
TARGET_LINK_LIBRARIES(ComplexNetworkCompare FeatureExtractors ComplexNetwork Utilities Qt5::Core Qt5::Widgets ${OpenCV_LIBS}  ${VTK_LIBRARIES})


