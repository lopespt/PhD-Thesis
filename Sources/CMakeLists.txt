

#Add ComplexNetwork dir to build ComplexNetwork lib
INCLUDE_DIRECTORIES(".")
ADD_SUBDIRECTORY(ComplexNetwork)
ADD_SUBDIRECTORY(FeatureExtractors)

#Add required packages to build all others executables
#FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5WebKitWidgets)
FIND_PACKAGE(LEMON REQUIRED)
INCLUDE_DIRECTORIES(${LEMON_INCLUDE_DIRS})
FIND_PACKAGE(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

#Set include directory to the root "include" dir
ADD_SUBDIRECTORY(Utilities)
ADD_SUBDIRECTORY(Segmentation)
ADD_SUBDIRECTORY(GuiUtilities)
ADD_SUBDIRECTORY(Experiments)
ADD_SUBDIRECTORY(Tests)

