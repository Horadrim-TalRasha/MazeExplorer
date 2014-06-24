BinName=MazeExplorer
CCX=g++
CC=gcc
CFLAGS = -g -Wall
CXXFLAGS = -g -Wall
OBJS = MazeExpl.o safemaze.o safemazeinterface.o explorer.o

ifeq ($(SKIP_TEST), true)
	CXXFLAGS += -DSKIP_TEST
endif

%.o : %.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

$(BinName) : $(OBJS) 
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) -lpthread

clean:
	@rm -rf *.o $(BinName) 2>/dev/null
