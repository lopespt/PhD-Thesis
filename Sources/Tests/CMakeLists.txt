
#FIND_LIBRARY(ComplexNetwork REQUIRED)
#FIND_LIBRARY(FeatureExtractors REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC TRUE)

#Build ResourcesTest
SET(ResourcesTest_Sources  ComplexNetworkResourcesTest/ComplexNetworkResourcesTest.cpp  )
ADD_EXECUTABLE(ComplexNetworkResourcesTest ${ResourcesTest_Sources} )
TARGET_LINK_LIBRARIES(ComplexNetworkResourcesTest ${Qt5Widgets_LIBRARIES}
    ${OpenCV_LIBRARIES} ComplexNetwork FeatureExtractors Utilities)



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
ADD_EXECUTABLE(AreaFeatureExtractionTest MACOSX_BUNDLE ${AreaFeatureExtractionTest_Sources})
TARGET_LINK_LIBRARIES(AreaFeatureExtractionTest ${Qt5Widgets_LIBRARIES} ${Qt5Gui_LIBRARIES} ${OpenCV_LIBRARIES} ComplexNetwork FeatureExtractors Utilities Segmentation)
