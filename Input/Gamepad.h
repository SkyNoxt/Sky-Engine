
#if defined(LINUX)

#include "LinuxGamepad.h"

typedef Sky::Input::LinuxGamepad Gamepad;

#elif defined(ANDROID)

#include "AndroidGamepad.h"

typedef Sky::Input::AndroidGamepad Gamepad;

#elif defined(WINDOWS)

#include "WindowsGamepad.h"

typedef Sky::Input::WindowsGamepad Gamepad;

#else

typedef Gamepad;

#endif
