project(UBCANNOTATION)

set(CMAKE_BUILD_TYPE Debug)

include(FindPkgConfig)
pkg_check_modules(GTK REQUIRED "gtk+-3.0")

set(ubc_annotation_src
        AnnotationClass.cpp
        AnnotationClassTable.cpp
	AnnotationEnumType.cpp
	AnnotationEnumUI.cpp
	AnnotationIntValue.cpp
	AnnotationObject.cpp
	AnnotationObjectUI.cpp
	AnnotationRecTimeValue.cpp
	AnnotationTable.cpp
	AnnotationTableUI.cpp
	AnnotationType.cpp
	AnnotationTypeTable.cpp
	AnnotationUIFactory.cpp
	AnnotationUINT64Value.cpp
	AnnotationValue.cpp
	ReachAnnotation.cpp
)

include_directories(
        ../UBCGUI
        ../UBCKinect
	../UBCUtil
	../Linux/Third-Party/libfreenect2/include/libfreenect2
	/usr/include
	/usr/include/eigen3
	${GTK_INCLUDE_DIRS}
)

add_library(
	ubcannotation STATIC
	${ubc_annotation_src}
)

add_library(
	ubcannotation SHARED
	${ubc_annotation_src}
)

set_property(TARGET ubcannotation PROPERTY CXX_STANDARD 11)
