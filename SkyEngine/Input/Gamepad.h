
#if defined(LINUX)

#include "LinuxGamepad.h"

typedef LinuxGamepad Gamepad;

#elif defined(ANDROID)

#include "AndroidGamepad.h"

typedef AndroidGamepad Gamepad;

#elif defined(WINDOWS)

#include "WindowsGamepad.h"

typedef WindowsGamepad Gamepad;

#endif
