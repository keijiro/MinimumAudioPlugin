SRCS=../PluginEntry.cpp
OBJS=$(SRCS:.cpp=.o)
OUTPUT=libSinOsc.so
CXXFLAGS=-I.. -O2 -fPIC -Wall -std=c++11
LDFLAGS=-shared -rdynamic -fPIC
CXX=g++

all: $(OUTPUT)

clean:
	rm -f $(OUTPUT) $(OBJS)

$(OUTPUT): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(OUTPUT) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
