CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = ./bin/main
OBJS = main.o functions.o

all: $(TARGET)

$(TARGET): $(OBJS) $(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: ./src/main.cpp 

functions.o:

clean: rm -f $(OBJS) $(TARGET)