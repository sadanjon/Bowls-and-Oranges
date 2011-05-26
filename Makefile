CXX=g++
CXXFLAGS=-Wall -O2
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)

TARGET=main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@