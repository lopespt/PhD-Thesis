
#FIND_LIBRARY(ComplexNetwork REQUIRED)
#FIND_LIBRARY(FeatureExtractors REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC TRUE)


#Build AreaFeatureExtractionTest
FILE(GLOB_RECURSE AreaFeatureExtractionTest_Sources *.cpp ${PhDThesis_SOURCE_DIR}/Sources/GuiUtilities/SupervisedImageViewerWidget.cpp)
ADD_EXECUTABLE(AreaFeatureExtractionTest ${AreaFeatureExtractionTest_Sources})
TARGET_LINK_LIBRARIES(AreaFeatureExtractionTest ${Qt5Widgets_LIBRARIES} ${Qt5Gui_LIBRARIES} ${OpenCV_LIBRARIES} ComplexNetwork FeatureExtractors Utilities )

INSTALL(TARGETS AreaFeatureExtractionTest DESTINATION bin)

