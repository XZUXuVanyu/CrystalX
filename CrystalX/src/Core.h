#pragma once

#ifdef CRYSTALX_WINDOWS
	#ifdef CRYSTALX_BUILD_DLL
		#define CRYSTALX_API __declspec(dllexport)
	#else
		#define CRYSTALX_API __declspec(dllimport)
	#endif
#else
	#error Only Support Windows
#endif
