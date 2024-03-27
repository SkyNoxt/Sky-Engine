
# Declaration of variables
CXXFLAGS = -c -std=c++23 -I . -Wall
LDFLAGS = 

EXECUTABLE = SkyEngine

ifdef OS
	CXXFLAGS += -D WINDOWS -Wno-deprecated-declarations
	LDFLAGS += -fuse-ld=lld -l user32 -l gdi32 -l xinput
	EXEEX = exe
	OBJEX = obj
else
	CXXFLAGS += -D LINUX
	LDFLAGS += 
	EXEEX = elf
	OBJEX = o
endif

# File names
HEADERS = $(shell find . -name "*.h")
SOURCES = $(shell find . -name "*.cpp")
OBJECTS = $(SOURCES:.cpp=.$(OBJEX))

TARGET = $(EXECUTABLE).$(EXEEX)

# Targets

all: release

debug: CXXFLAGS += -g
debug: $(TARGET)

release: CXXFLAGS += -Ofast -march=native -flto
release: LDFLAGS +=
release: $(TARGET)

# Link main target
$(TARGET): $(OBJECTS)
	$(CXX) $^ $(LDFLAGS) -o $@

# Compile source files
%.$(OBJEX): %.cpp %.h Makefile
	$(CXX) $(CXXFLAGS) $< -o $@

# Format code
format:
	clang-format -style=file -i $(HEADERS) $(SOURCES)

# Clean generated files
clean:
	$(RM) $(TARGET) $(OBJECTS)
