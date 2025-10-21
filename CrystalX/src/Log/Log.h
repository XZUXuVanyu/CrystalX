#pragma once
#define FMT_HEADER_ONLY
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"


namespace CrystalX
{
	//=============================================================================================
	/*
	包装了 spdlog[https://github.com/gabime/spdlog] 库 | Repackage of spdlog

	主要功能:
		1.实时输出日志                 - 控制台日志
		2.保存日志到文件               - 文件日志

	Functionalities:
		1.Print logs in realtime      - Console logging
		2.Save logs to local logfile  - File logging
	*/
	//=============================================================================================
	// CrystalX 日志类 | CrystalX Log Class
	class CRYSTALX_API Log
	{
	public:
		// 初始化日志系统 | Initialize logging system
		static void Initialize();

		// 关闭日志系统 | Disable logging system
		static void Disable();
		/// <summary>
		/// 启用/禁用文件日志 | Enable/disable file logging
		/// </summary>
		/// <param name="filename">
		/// 日志文件路径 | diretory to where log file is saved
		/// </param>
		static void EnableFileLogging(const std::string& filename, bool if_overwrite);
		static void DisableFileLogging();

		// 设置全局日志级别 | Set global log level
		static void SetLogLevel(spdlog::level::level_enum level);

		// 获取日志器实例 | Get logger instances
		inline static std::shared_ptr<spdlog::logger>& CoreLogger();
		inline static std::shared_ptr<spdlog::logger>& FileLogger();

		inline static bool GetInitializeState();
	private:
		// 核心日志器 | Core logger
		inline static std::shared_ptr<spdlog::logger> s_CoreLogger;

		// 文件日志器 | File logger (可选)
		inline static std::shared_ptr<spdlog::logger> s_FileLogger;

		// 初始化状态 | Initialization status
		inline static bool s_Initialized = false;
	};
}
