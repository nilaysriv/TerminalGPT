# Compiler
CXX = g++

# Compiler flags (-std=c++17 for modern features, -Wall for all warnings)
CXXFLAGS = -std=c++17 -Wall

# Libraries to link (libcurl for networking)
LIBS = -lcurl

# Target binary name
TARGET = terminalgpt

# Source files
SRC = terminalgpt.cpp

# Default rule: build the project
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

# Clean rule: remove the binary and object files
clean:
	rm -f $(TARGET)

# Run rule: build and then run immediately
run: all
	./$(TARGET)

.PHONY: all clean run