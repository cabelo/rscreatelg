VERSION   = 1.5
CXX       = dpcpp
LIBS      = `pkg-config --libs opencv4`  -lrealsense2 
CXXFLAGS  = `pkg-config --cflags opencv4` 
CXXFLAGSc = -fPIC -std=c++11 -Wall -Wextra -DUSE_BOOST_REGEX -DHAVE_OPENSSL -I.
prefix = /usr/local


all: rscreatelg

rscreatelg: main.cpp utils.hpp 
	$(CXX) $(CXXFLAGS) $(LIBS) $< -o $@

cleain:
	rm rscreatelg

install:
	 install -m 755 -c rscreatelg $(prefix)/bin/rscreatelg

uninstall:
	rm $(prefix)/bin/rscreatelg
