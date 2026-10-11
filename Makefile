CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -pedantic
TARGET = code
SRC = code.cpp

all: $(TARGET)

$(TARGET): $(SRC) MyList.hpp
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean

