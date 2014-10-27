FILE(GLOB_RECURSE sources *.cpp)
ADD_EXECUTABLE(DatabaseVisualizer ${sources})
TARGET_LINK_LIBRARIES(DatabaseVisualizer GuiUtilities Utilities FeatureExtractors Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL  ${OpenCV_LIBS}  ${VTK_LIBRARIES})
