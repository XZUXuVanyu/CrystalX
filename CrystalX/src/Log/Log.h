#pragma once
#define FMT_HEADER_ONLY
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"


namespace CrystalX
{
	// CrystalX 日志类 | CrystalX Log Class
	class CRYSTALX_API Log
	{
	public:
		/*基本操作 | Basic Log operations*/
		//-----------------------------------------------------------------------------------------------
		static void Initialize();
		static bool GetInitializeState();
		static void Disable();
		static void EnableFileLogging(const std::string& filename, bool if_overwrite);
		static void DisableFileLogging();
		static void SetLogLevel(spdlog::level::level_enum level);
		//-----------------------------------------------------------------------------------------------
		
		
		
	public:
		/*获取日志器实例 | Get logger instances*/
		//-----------------------------------------------------------------------------------------------
		inline static std::shared_ptr<spdlog::logger>& CoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& FileLogger() { return s_FileLogger; }
		//-----------------------------------------------------------------------------------------------



	private:
		/*初始化状态(全局单例) | Initialize state(global single instance)*/
		//-----------------------------------------------------------------------------------------------
		inline static std::atomic<bool> s_Initialized{ false };
		//-----------------------------------------------------------------------------------------------



	private:
		/*日志器实例(全局单例) | Logger instances(global single instance)*/
		//-----------------------------------------------------------------------------------------------
		inline static std::shared_ptr<spdlog::logger> s_CoreLogger;
		inline static std::shared_ptr<spdlog::logger> s_FileLogger;
		//-----------------------------------------------------------------------------------------------
	};
}
