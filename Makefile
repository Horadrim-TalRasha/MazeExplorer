BinName=MazeExplorer
CCX=g++
CC=gcc
CFLAGS = -g -Wall
CXXFLAGS = -g -Wall
OBJS = MazeExpl.o safemaze.o safemazeinterface.o explorer.o common/io/FileUtil.o

INCLUDEPATH = -I./common/io/ -I./common/log -I./common

ifeq ($(SKIP_TEST), true)
	CXXFLAGS += -DSKIP_TEST
endif

ifeq ($(COMPETE_TEST), true)
	CXXFLAGS += -DCOMPETE_TEST
endif

%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDEPATH) $< -o $@

$(BinName) : $(OBJS) 
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) -lpthread

clean:
	@rm -rf $(OBJS) $(BinName) 2>/dev/null
