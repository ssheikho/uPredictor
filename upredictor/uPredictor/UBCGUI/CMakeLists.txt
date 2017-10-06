project(UBCGUI)

include(${CMAKE_CURRENT_LIST_DIR}/../ProjectIncludes.cmake.in)

#set(CMAKE_BUILD_TYPE Debug)

include(FindPkgConfig)
pkg_check_modules(GTK REQUIRED "gtk+-3.0")

set(ubc_gui_src
	AutoResizeWindow.cpp
	CameraViewportManager.cpp
	ColumnLayout.cpp
	#EvenlySpacedRow.cpp #RowLayout is already evenly spaced
	GLFWWindowWrapper.cpp
	GLKeyHandler.cpp
	GridLayout.cpp
	GTKShutdownInterface.cpp
	ImageWindow.cpp
	LayoutContainer.cpp
	LayoutElement.cpp
	#NumberInfoList.cpp #Needs UBCEntry TypeRecipient
	PauseUnpauseUI.cpp
	RenderToggler.cpp
	RowLayout.cpp
	ScrollingWindow.cpp
	SimpleComboBox.cpp
	SimpleLabeledComboBox.cpp
	SimpleLabeledSlider.cpp
	SimpleLoadSaveInterface.cpp
	SimpleSlider.cpp
	UBCButton.cpp
	UBCEntry.cpp #TypeRecipient commented out
)

include_directories(
	../UBCUtil
	../Linux/Third-Party/libfreenect2/include/libfreenect2
	/usr/include
	/usr/include/eigen3
	${GTK_INCLUDE_DIRS}
)

add_library(
	ubcgui STATIC
	${ubc_gui_src}
)

add_library(
	ubcgui SHARED
	${ubc_gui_src}
)

set_property(TARGET ubcgui PROPERTY CXX_STANDARD 11)
