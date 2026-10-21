CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -lpthread
TARGET = bin/main

all: $(TARGET)

$(TARGET): src/main.cpp
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf bin/*

.PHONY: all clean