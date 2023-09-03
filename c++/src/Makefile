# Variables
CXX = g++
CXXFLAGS = -std=c++20
SRC = loader.cpp
OUT = loader.exe

# Default target
all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
