
#Create GuiUtilities library
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


FILE(GLOB_RECURSE Source_Files  *.cpp)
ADD_LIBRARY(GuiUtilities ${Source_Files})
TARGET_LINK_LIBRARIES(GuiUtilities ${Qt5Widgets_LIBRARIES} Utilities)


#Copy header files to root include dir
FILE(GLOB_RECURSE header_files ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
add_custom_command(
    TARGET GuiUtilities
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/GuiUtilities
    COMMAND cp -f ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/GuiUtilities/
)
