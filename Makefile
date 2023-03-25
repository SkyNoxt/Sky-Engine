
# Declaration of variables
CXXFLAGS = -c -std=c++20 -Ofast -flto -I . -I $(OPENCVINC) -Wall -Wno-narrowing
LDFLAGS = -Ofast -flto -L $(OPENCVLIB)

EXECUTABLE = SkyEngine

ifdef OS
	CXXFLAGS += -D WINDOWS
	LDFLAGS += -fuse-ld=lld -l xinput -l opencv_world460
	EXEEX = exe
	OBJEX = obj
else
	CXXFLAGS += -D LINUX
	LDFLAGS += -l opencv_core -l opencv_imgproc -l opencv_highgui
	EXEEX = elf
	OBJEX = o
endif

# File names
HEADERS = $(shell find . -name "*.h")
SOURCES = $(shell find . -name "*.cpp")
OBJECTS = $(SOURCES:.cpp=.$(OBJEX))

TARGET = $(EXECUTABLE).$(EXEEX)

# Main target linking
$(TARGET): $(OBJECTS)
	$(CXX) $^ $(LDFLAGS) -o $@

# Compile source files
%.$(OBJEX): %.cpp $(wildcard %.h)
	$(CXX) $(CXXFLAGS) $< -o $@

# Format code
format:
	clang-format -style=file -i $(HEADERS) $(SOURCES)

# Clean generated files
clean:
	$(RM) $(TARGET) $(OBJECTS)
