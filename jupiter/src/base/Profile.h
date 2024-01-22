#pragma once

// Own includes
#include "base/Defines.h"

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>

#define JPROFILE_MARK_FRAME FrameMark;
#define JPROFILE_FUNC(func_name) ZoneScopedN(func_name);
#define JPROFILE_SCOPE(scope) ZoneScopedN(scope);

#else
#define JPROFILE_MARK_FRAME
#define JPROFILE_FUNC(func_name)
#define JPROFILE_SCOPE(scope)

#endif  // TRACY_ENABLE
