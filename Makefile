CXX=g++
LDFLAGS=
EXE=mem
CPPFLAGS=

SRCS=main.cpp mem.hpp mem.cpp
OBJS=main.o mem.o

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(EXE) $(OBJS) $(LDLIBS) 

main.o: main.cpp mem.hpp
mem.o: mem.hpp mem.cpp

clean:
	rm -f $(OBJS) $(EXE)
