#pragma once

#include "Macro.h"

//DeBug�²ſ���
#if MACRO_TARGET_VER == MACRO_VER_DEBUG

//vld
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS

#include "vld.h"
#pragma comment(lib,"vld.lib")

#endif //vld

#endif // MACRO_TARGET_VER == MACRO_VER_DEBUG
