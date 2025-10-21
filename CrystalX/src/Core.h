#pragma once
#include <stdio.h>
#include <string>
#include <memory>
#include <functional>
#include <iostream>
#include <exception>

#include <glad/glad.h>
#include <glfw/glfw3.h>
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

//CHECKS AND ASSERTIONS
#ifdef CRYSTALX_CA_ON
	#define CRYSTALX_CHECK_WARN(flag, ...) {if (!(flag)) {CrystalX::Log::CoreLogger()->warn(##__VA_ARGS__);__debugbreak();}}
	#define CRYSTALX_ASSERT_ERR(flag, ...) {if (!(flag)) {CrystalX::Log::CoreLogger()->error(##__VA_ARGS__);__debugbreak();}}
#else
	#define CRYSTALX_CHECK_WARN(flag, ...)
	#define CRYSTALX_ASSERT_ERR(flag, ...)
#endif // CRSTALX_CA_ON


//简单的移位操作,获得 x 对应位的掩码 | Simple bit push marco to get a bitmask with bit x is 1
#define BIT_MASK(x) (1 << x)