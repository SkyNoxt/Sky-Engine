
# Declaration of variables
CC = g++
CC_FLAGS = -std=c++14 -flto -O3 -fopenmp -I. -Wall
LD_FLAGS = -flto -O3 -fopenmp -lopencv_core -lopencv_imgproc -lopencv_highgui

CC_DEBUG = -std=c++14 -g -fopenmp -I. -Wall
LD_DEBUG = -fopenmp -lopencv_core -lopencv_imgproc -lopencv_highgui

# File names
TARGET = SkyEngine
SOURCES = $(shell find . -name "*.cpp")
OBJECTS = $(SOURCES:.cpp=.o)

# Main target linking
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LD_FLAGS) -o $(TARGET)

# Compile source files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# Format code
format:
	clang-format $(SOURCES) 

# Clean generated files
clean:
	rm -f $(TARGET) $(OBJECTS)
