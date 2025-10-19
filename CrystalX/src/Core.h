#pragma once

//WINDOWS_PLATFORM
#ifdef CRYSTALX_WINDOWS
	#ifdef CRYSTALX_BUILD_DLL
		#define CRYSTALX_API __declspec(dllexport)
	#else
		#define CRYSTALX_API __declspec(dllimport)
	#endif
#else
	#error Only Support Windows
#endif

//简单的移位操作,获得 x 对应位的掩码 | Simple bit push marco to get a bitmask with bit x is 1
#define BIT_MASK(x) (1 << x)
