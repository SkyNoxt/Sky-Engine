
# Declaration of variables
OS = LINUX

CXXFLAGS = -std=c++17 -Ofast -flto -fopenmp -D $(OS) -I . -Wall -Wno-narrowing
LDFLAGS = -Ofast -flto -fopenmp -lopencv_core -lopencv_imgproc -lopencv_highgui

# File names
TARGET = SkyEngine
HEADERS = $(shell find . -name "*.h")
SOURCES = $(shell find . -name "*.cpp")
OBJECTS = $(SOURCES:.cpp=.o)

# Main target linking
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

# Compile source files
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Format code
format:
	clang-format -style=file -i $(HEADERS) $(SOURCES)

# Clean generated files
clean:
	rm -f $(TARGET) $(OBJECTS)
