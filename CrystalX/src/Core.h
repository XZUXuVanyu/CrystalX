#pragma once
#include <stdio.h>
#include <string>
#include <memory>
#include <functional>
#include <iostream>
#include <exception>
#include <unordered_map>

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

// ALTERABLE LOGLEVEL
// #define CRYSTALX_DEBUG_LOG to enable DEBUG level log
// #define CRYSTALX_RELEASE_LOG to enable RELEASE level log
// #define CRYSTALX_DIST_LOG to enable DIST level log
// RELEASE level for default
#if !defined(CRYSTALX_DEBUG_LOG) && !defined(CRYSTALX_RELEASE_LOG) && !defined(CRYSTALX_DIST_LOG)
#define CRYSTALX_RELEASE_LOG
#endif

#if defined(_MSC_VER)
#define CX_FUNCTION_SIGN __FUNCSIG__
#else
#define CX_FUNCTION_SIGN __PRETTY_FUNCTION__
#endif

#define CRYSTALX_GET_FULL_FUNCTION_NAME []() -> std::string \
{ \
    std::string sign = CX_FUNCTION_SIGN; \
    size_t start = sign.find("CrystalX::"); \
    if (start != std::string::npos) \
    { \
        size_t param_start = sign.find('(', start); \
        if (param_start != std::string::npos) \
        { \
            return sign.substr(start, param_start - start - 1); \
        } \
    } \
    size_t param_start = sign.find('('); \
    if (param_start != std::string::npos) \
    { \
        return sign.substr(0, param_start - 1); \
    } \
    return sign; \
}()

#define CRYSTALX_GET_FUNCTION_NAME []() -> std::string \
{ \
    std::string sign = CX_FUNCTION_SIGN; \
    size_t last_colon = sign.rfind("::"); \
    if (last_colon != std::string::npos) \
    { \
        size_t param_start = sign.find('(', last_colon); \
        if (param_start != std::string::npos) \
        { \
            return sign.substr(last_colon + 2, param_start - last_colon - 2); \
        } \
    } \
    size_t param_start = sign.find('('); \
    if (param_start != std::string::npos) \
    { \
        size_t name_start = sign.rfind(' ', param_start); \
        if (name_start != std::string::npos) \
        { \
            return sign.substr(name_start + 1, param_start - name_start - 1); \
        } \
    } \
    return "UnknownFunction"; \
}()

#ifdef CRYSTALX_DEBUG_LOG
#define CRYSTALX_LOG_TRACE(...)    \
        CrystalX::Log::CoreLogger()->trace("{}//{}", CRYSTALX_GET_FULL_FUNCTION_NAME, fmt::format(__VA_ARGS__))
#define CRYSTALX_LOG_DEBUG(...)    \
        CrystalX::Log::CoreLogger()->debug("{}//{}", CRYSTALX_GET_FULL_FUNCTION_NAME, fmt::format(__VA_ARGS__))
#define CRYSTALX_LOG_INFO(...)     \
        CrystalX::Log::CoreLogger()->info("{}//{}", CRYSTALX_GET_FULL_FUNCTION_NAME, fmt::format(__VA_ARGS__))
#define CRYSTALX_LOG_WARN(...)     \
        CrystalX::Log::CoreLogger()->warn("{}//{}", CRYSTALX_GET_FULL_FUNCTION_NAME, fmt::format(__VA_ARGS__))
#define CRYSTALX_LOG_ERROR(...)    \
        CrystalX::Log::CoreLogger()->error("{}//}", CRYSTALX_GET_FULL_FUNCTION_NAME, fmt::format(__VA_ARGS__))
#define CRYSTALX_LOG_CRITICAL(...) \
        CrystalX::Log::CoreLogger()->critical("{}//{}", CRYSTALX_GET_FULL_FUNCTION_NAME, fmt::format(__VA_ARGS__))

#elif defined(CRYSTALX_RELEASE_LOG)
#define CRYSTALX_LOG_TRACE(...)
#define CRYSTALX_LOG_DEBUG(...)
#define CRYSTALX_LOG_INFO(...)     \
        CrystalX::Log::CoreLogger()->info("{}//{}", CRYSTALX_GET_FUNCTION_NAME, fmt::format(__VA_ARGS__))
#define CRYSTALX_LOG_WARN(...)     \
        CrystalX::Log::CoreLogger()->warn("{}//{}", CRYSTALX_GET_FUNCTION_NAME, fmt::format(__VA_ARGS__))
#define CRYSTALX_LOG_ERROR(...)    \
        CrystalX::Log::CoreLogger()->error("{}//{}", CRYSTALX_GET_FUNCTION_NAME, fmt::format(__VA_ARGS__))
#define CRYSTALX_LOG_CRITICAL(...) \
        CrystalX::Log::CoreLogger()->critical("{}//{}", CRYSTALX_GET_FUNCTION_NAME, fmt::format(__VA_ARGS__))

#elif defined(CRYSTALX_DIST_LOG)
#define CRYSTALX_LOG_TRACE(...)
#define CRYSTALX_LOG_DEBUG(...)
#define CRYSTALX_LOG_INFO(...)
#define CRYSTALX_LOG_WARN(...)
#define CRYSTALX_LOG_ERROR(...)    \
        CrystalX::Log::CoreLogger()->error(__VA_ARGS__)
#define CRYSTALX_LOG_CRITICAL(...) \
        CrystalX::Log::CoreLogger()->critical(__VA_ARGS__)  
#endif

#define CRYSTALX_GET_KEYCODE(platformkeycode) CrystalX::KeyMapper::ToCrystalXKeyCode(platformkeycode)
#define CRYSTALX_GET_PLATFORM_CODE(keycode) CrystalX::KeyMapper::ToPlatformKeyCode(keycode)
#define CRYSTALX_GET_MODIFIER(platformkeycode) CrystalX::KeyMapper::ToCrystalXKeyModifier(platformkeycode)
#define CRYSTALX_GET_PLATFORM_MODS(modifier) CrystalX::KeyMapper::ToPlatformKeyModifier(modifier)

//简单的移位操作,获得 x 对应位的掩码 | Simple bit push marco to get a bitmask with bit x is 1
#define BIT_MASK(x) (1 << x)
