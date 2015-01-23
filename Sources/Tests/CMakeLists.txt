
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
IF(NOT CMAKE_SYSTEM_NAME MATCHES "Windows")
SET(ResourcesTest_Sources  ComplexNetworkResourcesTest/ComplexNetworkResourcesTest.cpp  )
ADD_EXECUTABLE(ComplexNetworkResourcesTest ${ResourcesTest_Sources} )
TARGET_LINK_LIBRARIES(ComplexNetworkResourcesTest ${Qt5Widgets_LIBRARIES}
    ${OpenCV_LIBRARIES} ComplexNetwork FeatureExtractors Utilities)
ENDIF()



#Build ConstructionTest
SET(ConstructionTest_Sources ComplexNetworkConstructionTest/ComplexNetworkConstructionTest.cpp)
ADD_EXECUTABLE(ComplexNetworkConstructionTest ${ConstructionTest_Sources})
TARGET_LINK_LIBRARIES(ComplexNetworkConstructionTest ${Qt5Widgets_LIBRARIES}
    ${OpenCV_LIBRARIES} ComplexNetwork FeatureExtractors Utilities)


#Build SegmenterTest
SET(SegmenterTest_Sources SegmenterTest/SegmenterTest.cpp)
ADD_EXECUTABLE(SegmenterTest ${SegmenterTest_Sources})
TARGET_LINK_LIBRARIES(SegmenterTest ${Qt5Widgets_LIBRARIES}
    ${OpenCV_LIBRARIES} ComplexNetwork FeatureExtractors Utilities Segmentation)

#Build AreaFeatureExtractionTest
FILE(GLOB_RECURSE AreaFeatureExtractionTest_Sources AreaFeatureExtractionTest/*.cpp ${PhDThesis_SOURCE_DIR}/Sources/GuiUtilities/SupervisedImageViewerWidget.cpp)
ADD_EXECUTABLE(AreaFeatureExtractionTest ${AreaFeatureExtractionTest_Sources})
TARGET_LINK_LIBRARIES(AreaFeatureExtractionTest ${Qt5Widgets_LIBRARIES} ${Qt5Gui_LIBRARIES} ${OpenCV_LIBRARIES} ComplexNetwork FeatureExtractors Utilities Segmentation)

INSTALL(TARGETS AreaFeatureExtractionTest DESTINATION bin)



#Build RandomWalkTest
FILE(GLOB_RECURSE RandomWalkTest_Sources RandomWalkTest/*.cpp)
ADD_EXECUTABLE(RandomWalkTest ${RandomWalkTest_Sources})
TARGET_LINK_LIBRARIES(RandomWalkTest ${Qt5Widgets_LIBRARIES} ${Qt5Gui_LIBRARIES} ${OpenCV_LIBRARIES} ComplexNetwork FeatureExtractors Utilities Segmentation)


MESSAGE(STATUS ${CMAKE_INSTALL_PREFIX})

