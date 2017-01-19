CXX = g++ -std=c++11
CXXFLAGS = -Wall -Wextra
USR = -I/usr/include/ -L/usr/local/libs/
GL = -lglfw3 -lGL -lGLU -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi
ADDITIONALS = -ldl -lXinerama -lXcursor
MATH = -lm

COMMAND = $(CXX) $(CXXFLAGS) $(USR)
LIBS = -lstdc++ $(GL) $(ADDITIONALS) $(MATH)

all : MemoryGame

clean :
	rm -f *.o

refresh : clean all

MemoryGame : MemoryGame.o GLSLloader.o GLGameDrawer.o
	$(COMMAND) MemoryGame.o GLSLloader.o GLGameDrawer.o -o MemoryGame $(LIBS)

MemoryGame.o : MemoryGame.cpp GLSLloader.hpp GLGameDrawer.hpp
	$(COMMAND) -c MemoryGame.cpp -o MemoryGame.o $(LIBS)

GLGameDrawer.o : GLGameDrawer.cpp GLGameDrawer.hpp
	$(COMMAND) -c GLGameDrawer.cpp -o GLGameDrawer.o $(LIBS)

GLSLloader.o : GLSLloader.cpp GLSLloader.hpp
	$(COMMAND) -c GLSLloader.cpp -o GLSLloader.o $(LIBS)

