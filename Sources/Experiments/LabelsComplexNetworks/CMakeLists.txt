
INCLUDE_DIRECTORIES(../../)
INCLUDE_DIRECTORIES(.)
SET(sources main.cpp gMainWindow.cpp)
ADD_EXECUTABLE(LabelsComplexNetworkExperiment ${sources})
TARGET_LINK_LIBRARIES(LabelsComplexNetworkExperiment FeatureExtractors ComplexNetwork Utilities Qt5::Core Qt5::Widgets Qt5::OpenGL  ${OpenCV_LIBS}  ${VTK_LIBRARIES})
