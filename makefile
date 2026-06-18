CXX := g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I./libraries/include -I./libraries/include/glad -I./src/headers
LDFLAGS = -lGL -lglfw

SRC = src/main.cpp
TARGET = ./bin/main
LIBRARYFILES = -L./libraries/lib

main: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LIBRARYFILES) -o $(TARGET) 

.PHONY: clean

clean: 
	rm -rf ./bin/*