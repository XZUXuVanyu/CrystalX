//utf8
#pragma once

#include <memory>

#include "../Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace CrystalX
{
	//CrystalX 日志类 | CrystalX Log Class
	class CRYSTALX_API Log
	{
	public:

		//初始化 CrystalX::Log | Initialize CrystalX::Log 
		static void Init();

		/// 返回 CRYSTALX_DEBUG 运行时下的日志器 | Return the CoreLogger under RUNTIME_DEBUG
		inline static std::shared_ptr<spdlog::logger>& CoreLogger() { return CrstalX_CoreLogger; }
		/// 返回 CRYSTALX_RELEASE 运行时下的日志器 | Return the ClientLogger under RELEASE_DEBUG
		inline static std::shared_ptr<spdlog::logger>& ClientLogger() { return CrstalX_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> CrstalX_CoreLogger;
		static std::shared_ptr<spdlog::logger> CrstalX_ClientLogger;
	};
}

//DEBUG运行时 | RUNTIME_DEBUG
#ifdef CRYSTALX_DEBUG 
	#define CRYSTALX_CORE_FATAL(...)     ::CrystalX::Log::CoreLogger()->fatal(__VA_ARGS__)
	#define CRYSTALX_CORE_ERROR(...)     ::CrystalX::Log::CoreLogger()->error(__VA_ARGS__)
	#define CRYSTALX_CORE_WARN(...)      ::CrystalX::Log::CoreLogger()->warn(__VA_ARGS__)
	#define CRYSTALX_CORE_INFO(...)      ::CrystalX::Log::CoreLogger()->info(__VA_ARGS__)
	#define CRYSTALX_CORE_TRACE(...)     ::CrystalX::Log::CoreLogger()->trace(__VA_ARGS__)
#endif // CRYSTALX_DEBUG

//RELEASE运行时 | RUNTIME_RELEASE
#ifdef CRYSTALX_RELEASE
	#define CRYSTALX_FATAL(...)   ::CrystalX::Log::ClientLogger()->fatal(__VA_ARGS__)
	#define CRYSTALX_ERROR(...)   ::CrystalX::Log::ClientLogger()->error(__VA_ARGS__)
	#define CRYSTALX_WARN(...)    ::CrystalX::Log::ClientLogger()->warn(__VA_ARGS__)
	#define CRYSTALX_INFO(...)    ::CrystalX::Log::ClientLogger()->info(__VA_ARGS__)
	#define CRYSTALX_TRACE(...)   ::CrystalX::Log::ClientLogger()->trace(__VA_ARGS__)
#endif // CRYSTALX_RELEASE