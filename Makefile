CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -lpthread -lsqlite3
TARGET = bin/main
TEST_TARGET = bin/tester

all: $(TARGET)
tester: $(TEST_TARGET)

$(TARGET): src/main.cpp
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $< -o $@

$(TEST_TARGET): src/tester.cpp
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf bin/*

.PHONY: all clean
