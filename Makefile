
TARGET = da
vpath %.h include
vpath %.cpp src
CPPFLAGS = -I include -O2
CC = g++ -std=c++11 -std=c++14
SRCS = DoubleArray.cpp KeySort.cpp main.cpp 
OBJS := $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CC) $(CPPFLAGS) $^ -o $@

.cpp.o:
	$(CC) $(CPPFLAGS) -c -o $@ $^

clean: 
	rm -f *.o

