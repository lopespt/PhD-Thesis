
#FIND_LIBRARY(ComplexNetwork REQUIRED)
#FIND_LIBRARY(FeatureExtractors REQUIRED)
#FIND_LIBRARY(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)


#Build ResourcesTest
SET(ResourcesTest_Sources  ComplexNetworkResourcesTest/ComplexNetworkResourcesTest.cpp  )
ADD_EXECUTABLE(ComplexNetworkResourcesTest ${ResourcesTest_Sources} )
TARGET_LINK_LIBRARIES(ComplexNetworkResourcesTest ${Qt5Widgets_LIBRARIES}
    ${OpenCV_LIBRARIES} ComplexNetwork FeatureExtractors Utilities)



SET(ConstructionTest_Sources ComplexNetworkConstructionTest/ComplexNetworkConstructionTest.cpp)
ADD_EXECUTABLE(ComplexNetworkConstructionTest ${ConstructionTest_Sources})
TARGET_LINK_LIBRARIES(ComplexNetworkConstructionTest ${Qt5Widgets_LIBRARIES}
    ${OpenCV_LIBRARIES} ComplexNetwork FeatureExtractors Utilities)

MESSAGE(STATUS ${Qt5Widgets_FOUND})
FOREACH(i ${Qt5Widgets_INCLUDE_DIRS})
    MESSAGE(STATUS ${i})
ENDFOREACH(i)
