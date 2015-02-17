
#FIND_LIBRARY(ComplexNetwork REQUIRED)
#FIND_LIBRARY(FeatureExtractors REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)
FIND_PACKAGE(VTK REQUIRED)
FIND_PACKAGE(lemon REQUIRED)
INCLUDE(${VTK_USE_FILE})

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC TRUE)


#Build ResourcesTest only on Posix Platforms
IF(NOT CMAKE_SYSTEM_NAME MATCHES "Windows")
SET(ResourcesTest_Sources ComplexNetworkResourcesTest.cpp  )
ADD_EXECUTABLE(ComplexNetworkResourcesTest ${ResourcesTest_Sources} )
TARGET_LINK_LIBRARIES(ComplexNetworkResourcesTest ${Qt5Widgets_LIBRARIES} ${LEMON_LIBRARIES}
    ${OpenCV_LIBRARIES} ComplexNetwork FeatureExtractors )
ENDIF()


