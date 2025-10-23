#include "Log.h"

namespace CrystalX
{
	/*基本操作实现 | Basic operation implementations*/
	//----------------------------------------------------------------------------------------------
	void Log::Initialize()
	{
		if (s_Initialized) {
			return;
		}

		try {
			// 设置控制台日志格式 | Set console log format
			spdlog::set_pattern("%^[%Y-%m-%d %H:%M:%S] [%n] [%l]: %v%$");

			// 创建控制台日志器 | Create console logger
			s_CoreLogger = spdlog::stdout_color_mt("CrystalX");
			s_CoreLogger->set_level(spdlog::level::trace);

			s_Initialized = true;

			CRYSTALX_info("core log system initialized successfully");
		}
		catch (const spdlog::spdlog_ex& ex) {
			std::cerr << "[error] Core Log initialization failed: " << ex.what() << std::endl;
		}
	}
	void Log::Disable()
	{
		if (s_Initialized) {
			s_CoreLogger->info("disabling log system");
			DisableFileLogging();
			s_CoreLogger.reset();
			s_Initialized = false;
			std::cout << "[info] Core Log system shutdown complete." << std::endl;
		}
	}
	void Log::EnableFileLogging(const std::string& filename, bool if_overwrite)
	{
		if (!s_Initialized) {
			Initialize();
		}

		try {
			// 创建文件日志器 | Create file logger
			//todo: if overwrite?
			s_FileLogger = spdlog::basic_logger_mt("file_logger", filename, if_overwrite);
			s_FileLogger->set_level(spdlog::level::trace);
			s_FileLogger->set_pattern("[%Y-%m-%d %H:%M:%S] [%n] [%l]: %v");

			s_CoreLogger->sinks().push_back(s_FileLogger->sinks().back());
			CRYSTALX_debug("file log system enabled, view logfile at \".\\{}\"", filename);
		}
		catch (const spdlog::spdlog_ex& ex) {
			s_CoreLogger->error("failed to enable file log system: {}", ex.what());
		}
	}
	void Log::DisableFileLogging()
	{
		if (s_FileLogger) {
			CRYSTALX_trace("Disabling file logging");
			s_FileLogger->flush();

			// 从核心日志器中移除文件sink | remove file sink from CoreLogger sink
			auto& sinks = s_CoreLogger->sinks();
			if (!sinks.empty() && s_FileLogger) {
				auto file_sink = s_FileLogger->sinks().back();
				sinks.erase(std::remove(sinks.begin(), sinks.end(), file_sink), sinks.end());
			}

			s_FileLogger.reset();
			CRYSTALX_info("File logging successfully disabled");
		}
	}
	void Log::SetLogLevel(spdlog::level::level_enum level)
	{
		if (s_CoreLogger) {
			s_CoreLogger->set_level(level);
			if (s_FileLogger) {
				s_FileLogger->set_level(level);
			}
			else {
				CRYSTALX_warn("haven't initialize file log system yet");
			}
		}
		else {
			std::cout << "[warning] haven't initialize core log system yet" << std::endl;
		}
	}
	bool Log::GetInitializeState()
	{
		return s_Initialized;
	}
	//----------------------------------------------------------------------------------------------
}

//todo : use marco or sth else to add a (caller):msg type output