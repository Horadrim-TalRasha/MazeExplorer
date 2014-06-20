BinName=MazeExplorer
CCX=g++
CC=gcc
CFLAGS = -g -Wall
CXXFLAGS = -g -Wall
OBJS = MazeExpl.o safemaze.o safemazeinterface.o

%.o : %.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

$(BinName) : $(OBJS) 
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

clean:
	@rm -rf *.o $(BinName) 2>/dev/null
