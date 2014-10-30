
INCLUDE_DIRECTORIES(../../)
INCLUDE_DIRECTORIES(.)
SET(sources main.cpp )
ADD_EXECUTABLE(AreaComplexNetworkExperiment ${sources})
TARGET_LINK_LIBRARIES(AreaComplexNetworkExperiment FeatureExtractors ComplexNetwork Utilities Qt5::Core Qt5::Widgets Qt5::OpenGL  ${OpenCV_LIBS}  ${VTK_LIBRARIES})
