#pragma once

// Export/import jupiter api
#ifdef JUPITER_PLATFORM_WINDOWS
	#ifdef JUPITER_BUILD_DLL
		#define JUPITER_API __declspec(dllexport)
	#else
		#define JUPITER_API __declspec(dllimport)
	#endif
#else
	#error jupiter engine supports only Windows
#endif
