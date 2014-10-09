

#Add ComplexNetwork dir to build ComplexNetwork lib
ADD_SUBDIRECTORY(ComplexNetwork)
ADD_SUBDIRECTORY(FeatureExtractors)

#Add required packages to build all others executables
#FIND_PACKAGE(Qt5Widgets REQUIRED)
#FIND_PACKAGE(OpenCV REQUIRED)

#Set include directory to the root "include" dir
INCLUDE_DIRECTORIES(".")
ADD_SUBDIRECTORY(Utilities)
ADD_SUBDIRECTORY(Segmentation)
ADD_SUBDIRECTORY(GuiUtilities)
ADD_SUBDIRECTORY(Experiments)


ADD_SUBDIRECTORY(Tests)

