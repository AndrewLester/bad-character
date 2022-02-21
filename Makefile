EXENAME = bmoore
OBJS = main.o bmoore.o

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp bmoore.h
	$(CXX) $(CXXFLAGS) main.cpp

bmoore.o : bmoore.cpp bmoore.h
	$(CXX) $(CXXFLAGS) bmoore.cpp

test: catchmain.o tests.o bmoore.o
	$(LD) catchmain.o tests.o  bmoore.o $(LDFLAGS) -o test

catchmain.o : catchmain.cpp catch.hpp
	$(CXX) $(CXXFLAGS) catchmain.cpp

tests.o : tests.cpp catch.hpp bmoore.cpp bmoore.h 
	$(CXX) $(CXXFLAGS) tests.cpp

clean :
	-rm -f *.o $(EXENAME) test
