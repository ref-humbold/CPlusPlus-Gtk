CXX = g++ -std=c++11
CXXFLAGS = -Wall -Wextra

all : generator_pi

clean :
	rm -f *.o

refresh : clean all

generator_pi : generator_pi.cpp
	$(CXX) $(CXXFLAGS) -Wall -Wextra generator_pi.cpp -o generator_pi
