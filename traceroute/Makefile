CXX = g++ -std=c++11
CXXFLAGS = -Wall -Wextra

all : traceroute

clean :
	rm -f *.o

distclean : clean
	rm -f traceroute

refresh : clean all

traceroute : IPAddress.o RawSocket.o ICMPReceiver.o ICMPSender.o ICMPController.o traceroute.o
	$(CXX) $(CXXFLAGS) IPAddress.o RawSocket.o ICMPReceiver.o ICMPSender.o ICMPController.o traceroute.o -o traceroute

traceroute.o : traceroute.cpp
	$(CXX) $(CXXFLAGS) -c traceroute.cpp -o traceroute.o

ICMPController.o : ICMPController.cpp
	$(CXX) $(CXXFLAGS) -c ICMPController.cpp -o ICMPController.o

ICMPSender.o : ICMPSender.cpp
	$(CXX) $(CXXFLAGS) -c ICMPSender.cpp -o ICMPSender.o

ICMPReceiver.o : ICMPReceiver.cpp
	$(CXX) $(CXXFLAGS) -c ICMPReceiver.cpp -o ICMPReceiver.o

RawSocket.o : RawSocket.cpp
	$(CXX) $(CXXFLAGS) -c RawSocket.cpp -o RawSocket.o

IPAddress.o : IPAddress.cpp
	$(CXX) $(CXXFLAGS) -c IPAddress.cpp -o IPAddress.o
