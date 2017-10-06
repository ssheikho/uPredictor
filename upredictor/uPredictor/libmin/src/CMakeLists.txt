add_library (min SHARED
	levmardif.cc
	libmin.cc
	rtlevmar.cc
	rtminimizable.cc

	minimizable.cc	
	minimizablewithderiv.cc	
	minwpin.cc
)

add_library (min_static STATIC
	levmardif.cc
	libmin.cc
	rtlevmar.cc
	rtminimizable.cc

	minimizable.cc	
	minimizablewithderiv.cc	
	minwpin.cc
)

include_directories (
	../include
	/home/justin/Research/ThirdParty/levmar-2.6
	/usr/include/opencv 
	/usr/local/include) 

INSTALL(FILES libmin.so DESTINATION /lib)
