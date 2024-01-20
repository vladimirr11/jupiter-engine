#pragma once

// Own includes
#include "base/Defines.h"

#ifdef TRACY_ENABLE
#include "tracy/Tracy.hpp"

#define JPROFILE_MARK_FRAME FrameMark;

#else
#define JPROFILE_MARK_FRAME

#endif  // !TRACY_ENABLE
