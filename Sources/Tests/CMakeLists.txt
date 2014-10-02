
FIND_LIBRARY(ComplexNetwork REQUIRED)

SET(ResourcesTest_Sources  ComplexNetworkResourcesTest/ComplexNetworkResourcesTest.cpp  )
SET(ConstructionTest_Sources ComplexNetworkConstructionTest/ComplexNetworkConstructionTest.cpp)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
      message(STATUS "dir='${dir}'")
  endforeach()

ADD_EXECUTABLE(ComplexNetworkResourcesTest ${ResourcesTest_Sources}
    ${Utilities_SRC} ${ComplexNetwork_SRC} ${FeatureExtractors_SRC} )
TARGET_LINK_LIBRARIES(ComplexNetworkResourcesTest ${Qt5Widgets_LIBRARIES} ${OpenCV_LIBRARIES} ComplexNetwork )

ADD_EXECUTABLE(ComplexNetworkConstructionTest ${ConstructionTest_Sources}
    ${Utilities_SRC} ${FeatureExtractors_SRC} ${ComplexNetwork_SRC})
TARGET_LINK_LIBRARIES(ComplexNetworkConstructionTest ${Qt5Widgets_LIBRARIES} ${OpenCV_LIBRARIES} ComplexNetwork )
