BinName=MazeExplorer
CCX=g++
CC=gcc
CFLAGS = -g -Wall
CXXFLAGS = -g -Wall
OBJS = MazeManualExpl.o safemaze.o safemazeinterface.o explorer.o common/io/FileUtil.o common/network/mazenet.o

INCLUDEPATH = -I./common/io/ -I./common/log -I./common -I./common/network -I./strategy -I./common/protocol

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
