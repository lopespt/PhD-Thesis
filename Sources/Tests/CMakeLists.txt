
FIND_LIBRARY(ComplexNetwork REQUIRED)

FILE(GLOB_RECURSE sources main.cpp  ../FeatureExtractors/* ../Utilities/*)
ADD_EXECUTABLE(Test1 ${sources})
TARGET_LINK_LIBRARIES(Test1 ${Qt5Widgets_LIBRARIES} ${OpenCV_LIBRARIES}
    ${ComplexNetwork_LIBRARIES} )

