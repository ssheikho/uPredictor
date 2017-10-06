project(UBCUTIL)

set(CMAKE_BUILD_TYPE Debug)

set(ubc_util_src
	DefaultShutdownInterface.cpp
	DragRect.cpp
	ExternalUpdateCollection.cpp
	ExternalUpdateThread.cpp
	FileIndex.cpp
	ImageChannelBroadcaster.cpp
	#LameLock.cpp
	LongValueArrayEU.cpp
	ParseMathematica.cpp
	Pause.cpp
	RefCounter.cpp
	ShutdownContainer.cpp
	ShutdownInterface.cpp
	UBCUtil.cpp
	VideoRescaler.cpp
)

include_directories(
	/usr/include
	/usr/include/eigen3
	#/usr/include/nvidia-361
	/usr/include/opencv
	../Linux/Third-Party/libfreenect2/include/libfreenect2
)

add_library(
	ubcutil SHARED
	${ubc_util_src}
)

add_library(
	ubcutil STATIC
	${ubc_util_src}
)

set_property(TARGET ubcutil PROPERTY CXX_STANDARD 11)
