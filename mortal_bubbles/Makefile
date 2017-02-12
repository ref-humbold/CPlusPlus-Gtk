CXX = g++ -std=c++11
CXXFLAGS = -Wall -Wextra
USR = -I/usr/include/ -L/usr/local/libs/
GL = -lglfw3 -lGL -lGLU -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi
ADDITIONALS = -ldl -lXinerama -lXcursor
MATH = -lm

COMMAND = $(CXX) $(CXXFLAGS) $(USR)
LIBS = -lstdc++ $(GL) $(ADDITIONALS) $(MATH)

all : MortalBubbles

clean :
	rm -f *.o

refresh : clean all

MortalBubbles : MortalBubbles.o GLSLloader.o GameControler.o GameAquarium.o GameBubble.o GamePlayer.o
	$(COMMAND) MortalBubbles.o GLSLloader.o GameControler.o GameAquarium.o GameBubble.o GamePlayer.o -o MortalBubbles $(LIBS)

MortalBubbles.o : MortalBubbles.cpp GLSLloader.hpp GameControler.hpp
	$(COMMAND) -c MortalBubbles.cpp -o MortalBubbles.o $(LIBS)

GameControler.o : GameControler.cpp GameControler.hpp GameAquarium.hpp GameBubble.hpp GamePlayer.hpp
	$(COMMAND) -c GameControler.cpp -o GameControler.o $(LIBS)

GamePlayer.o : GamePlayer.cpp GamePlayer.hpp
	$(COMMAND) -c GamePlayer.cpp -o GamePlayer.o $(LIBS)

GameBubble.o : GameBubble.cpp GameBubble.hpp
	$(COMMAND) -c GameBubble.cpp -o GameBubble.o $(LIBS)

GameAquarium.o : GameAquarium.cpp GameAquarium.hpp
	$(COMMAND) -c GameAquarium.cpp -o GameAquarium.o $(LIBS)

GLSLloader.o : GLSLloader.cpp GLSLloader.hpp
	$(COMMAND) -c GLSLloader.cpp -o GLSLloader.o $(LIBS)

