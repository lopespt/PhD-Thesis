#FIND_LIBRARY(ComplexNetwork REQUIRED)
#FIND_LIBRARY(FeatureExtractors REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC TRUE)


#Build ResourcesTest only on Posix Platforms
#IF(NOT CMAKE_SYSTEM_NAME MATCHES "Windows")
ADD_EXECUTABLE(IntersectionQLineQPolygonTest main.cpp IntersectionTest.cpp IntersectionTest.h)
TARGET_LINK_LIBRARIES(IntersectionQLineQPolygonTest ${Qt5Widgets_LIBRARIES} ${LEMON_LIBRARIES}
    ${OpenCV_LIBRARIES} ComplexNetwork FeatureExtractors Utilities )
#ENDIF()

