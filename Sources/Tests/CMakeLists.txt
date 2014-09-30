
FIND_LIBRARY(ComplexNetwork REQUIRED)

FILE(GLOB_RECURSE sources NetworkConstructionTest.cpp  ../FeatureExtractors/* ../Utilities/*)
ADD_EXECUTABLE(NetworkConstructionTest ${sources})
TARGET_LINK_LIBRARIES(NetworkConstructionTest ${Qt5Widgets_LIBRARIES} ${OpenCV_LIBRARIES} ComplexNetwork )

