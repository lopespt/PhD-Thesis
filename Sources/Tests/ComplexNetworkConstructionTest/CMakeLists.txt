
#FIND_LIBRARY(ComplexNetwork REQUIRED)
#FIND_LIBRARY(FeatureExtractors REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC TRUE)


#Build ConstructionTest
SET(ConstructionTest_Sources ComplexNetworkConstructionTest.cpp)
ADD_EXECUTABLE(ComplexNetworkConstructionTest ${ConstructionTest_Sources})
TARGET_LINK_LIBRARIES(ComplexNetworkConstructionTest ${Qt5Widgets_LIBRARIES}
    ${OpenCV_LIBRARIES} ComplexNetwork FeatureExtractors Utilities)



