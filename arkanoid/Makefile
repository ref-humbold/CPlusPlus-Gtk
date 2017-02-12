CXX = g++ -std=c++11
CXXFLAGS = -Wall -Wextra
USR = -I/usr/include/ -L/usr/local/libs/
GL = -lglfw3 -lGL -lGLU -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi
ADDITIONALS = -ldl -lXinerama -lXcursor
MATH = -lm

COMMAND = $(CXX) $(CXXFLAGS) $(USR)
LIBS = -lstdc++ $(GL) $(ADDITIONALS) $(MATH)

all : Arkanoid

clean :
	rm -f *.o

refresh : clean all

Arkanoid : Arkanoid.o GLSLloader.o GameElement.o
	$(COMMAND) Arkanoid.o GLSLloader.o GameElement.o -o Arkanoid $(LIBS)

Arkanoid.o : Arkanoid.cpp GLSLloader.hpp GameElement.hpp
	$(COMMAND) -c Arkanoid.cpp -o Arkanoid.o $(LIBS)

GameElement.o : GameElement.cpp GameElement.hpp
	$(COMMAND) -c GameElement.cpp -o GameElement.o $(LIBS)

GLSLloader.o : GLSLloader.cpp GLSLloader.hpp
	$(COMMAND) -c GLSLloader.cpp -o GLSLloader.o $(LIBS)

