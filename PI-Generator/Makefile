CXX = g++ -std=c++11
CXXFLAGS = -Wall -Wextra
GTKMM = `pkg-config gtkmm-3.0 --cflags --libs`

all : generator_pi

clean :
	rm -f *.o

refresh : clean all

generator_pi : generator_pi.cpp
	$(CXX) $(CXXFLAGS) generator_pi.cpp -o generator_pi $(GTKMM)

