CXX = g++ -std=c++11
CXXFLAGS = -Wall -Wextra
ANL = -I/home/anl/include/ -L/home/anl/libs/
USR = -I/usr/include/ -L/usr/local/libs/
GL = -lglfw3 -lGL -lGLU -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi
KALETA = -ldl -lXinerama -lXcursor
MATH = -lm

COMMAND = $(CXX) $(CXXFLAGS) $(USR) $(ANL)
LIBS = -lstdc++ $(GL) $(KALETA) $(MATH)

all : Teren

clean :
	rm -f *.o

refresh : clean all

Teren : Teren.o GLSLloader.o Area.o Camera.o Detailing.o Earth.o
	$(COMMAND) Teren.o GLSLloader.o Area.o Camera.o Detailing.o Earth.o -o Teren $(LIBS)

Teren.o : Teren.cpp GLSLloader.hpp Area.hpp Camera.hpp Detailing.hpp Earth.hpp
	$(COMMAND) -c Teren.cpp -o Teren.o $(LIBS)

Camera.o : Camera.cpp Camera.hpp Area.hpp Detailing.hpp Earth.hpp
	$(COMMAND) -c Camera.cpp -o Camera.o $(LIBS)

Area.o : Area.cpp Area.hpp Detailing.hpp
	$(COMMAND) -c Area.cpp -o Area.o $(LIBS)

Detailing.o : Detailing.cpp Detailing.hpp
	$(COMMAND) -c Detailing.cpp -o Detailing.o $(LIBS)

Earth.o : Earth.cpp Earth.hpp
	$(COMMAND) -c Earth.cpp -o Earth.o $(LIBS)

GLSLloader.o : GLSLloader.cpp GLSLloader.hpp
	$(COMMAND) -c GLSLloader.cpp -o GLSLloader.o $(LIBS)
