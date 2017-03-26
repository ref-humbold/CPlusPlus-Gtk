CXX = g++ -std=c++11
CXXFLAGS = -Wall -Wextra

all : traceroute

clean :
	rm -f *.o

distclean : clean
	rm -f traceroute

traceroute : traceroute.o SocketController.o SocketSender.o SocketReceiver.o RawSocket.o
	$(CXX) $(CXXFLAGS) traceroute.o SocketController.o SocketSender.o SocketReceiver.o RawSocket.o -o traceroute

traceroute.o : traceroute.cpp SocketController.hpp SocketSender.hpp SocketReceiver.hpp RawSocket.hpp
	$(CXX) $(CXXFLAGS) -c traceroute.cpp -o traceroute.o

SocketController.o : SocketController.cpp SocketController.hpp SocketSender.hpp SocketReceiver.hpp RawSocket.hpp
	$(CXX) $(CXXFLAGS) -c SocketController.cpp -o SocketController.o

SocketSender.o : SocketSender.cpp RawSocket.hpp
	$(CXX) $(CXXFLAGS) -c SocketSender.cpp -o SocketSender.o

SocketReceiver.o : SocketReceiver.cpp RawSocket.hpp
	$(CXX) $(CXXFLAGS) -c SocketReceiver.cpp -o SocketReceiver.o

RawSocket.o : RawSocket.cpp RawSocket.hpp
	$(CXX) $(CXXFLAGS) -c RawSocket.cpp -o RawSocket.o
