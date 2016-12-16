#!/bin/sh

echo "Makefile maker"
mkdir src include
mv *.cpp src/
mv *.h include/

nkf -w --overwrite src/*.cpp
nkf -w --overwrite include/*.h

files="src/*.cpp"
srcs=()
for val in $files ;do
	srcs+="${val##*/} "
done

echo "
TARGET = $1
vpath %.h include
vpath %.cpp src
CPPFLAGS = -I include -O2
CC = g++ -std=c++11
SRCS = ${srcs[*]}
OBJS := \$(SRCS:.cpp=.o)

\$(TARGET): \$(OBJS)
	\$(CC) \$(CPPFLAGS) $^ -o \$@

.cpp.o:
	\$(CC) \$(CPPFLAGS) -c -o \$@ $^

clean: 
	rm -f *.o
	rm \$(TARGET)
" > Makefile

