CXX = g++ -std=c++11
CXXFLAGS = -Wall -Wextra

all : traceroute

clean :
	rm -f *.o

refresh : clean all

traceroute : traceroute.o ICMPController.o ICMPSender.o ICMPReceiver.o RawSocket.o IPAddress.o
	$(CXX) $(CXXFLAGS) traceroute.o ICMPController.o ICMPSender.o ICMPReceiver.o RawSocket.o IPAddress.o -o traceroute

traceroute.o : traceroute.cpp ICMPController.hpp ICMPSender.hpp ICMPReceiver.hpp RawSocket.hpp IPAddress.hpp
	$(CXX) $(CXXFLAGS) -c traceroute.cpp -o traceroute.o

ICMPController.o : ICMPController.cpp ICMPController.hpp ICMPSender.hpp ICMPReceiver.hpp RawSocket.hpp IPAddress.hpp
	$(CXX) $(CXXFLAGS) -c ICMPController.cpp -o ICMPController.o

ICMPSender.o : ICMPSender.cpp RawSocket.hpp IPAddress.hpp
	$(CXX) $(CXXFLAGS) -c ICMPSender.cpp -o ICMPSender.o

ICMPReceiver.o : ICMPReceiver.cpp RawSocket.hpp IPAddress.hpp
	$(CXX) $(CXXFLAGS) -c ICMPReceiver.cpp -o ICMPReceiver.o

RawSocket.o : RawSocket.cpp RawSocket.hpp
	$(CXX) $(CXXFLAGS) -c RawSocket.cpp -o RawSocket.o

IPAddress.o : IPAddress.cpp IPAddress.hpp
	$(CXX) $(CXXFLAGS) -c IPAddress.cpp -o IPAddress.o
