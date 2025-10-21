#include "Log.h"

namespace CrystalX
{
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

			s_CoreLogger->info("Core Log system initialized successfully");
		}
		catch (const spdlog::spdlog_ex& ex) {
			std::cerr << "[error] Core Log initialization failed: " << ex.what() << std::endl;
		}
	}

	void Log::Disable()
	{
		if (s_Initialized) {
			s_CoreLogger->info("Disabling log system");
			DisableFileLogging();
			s_CoreLogger.reset();
			s_Initialized = false;
			std::cout << "[info] Core Log system shutdown complete." << std::endl;
		}
	}

	void Log::EnableFileLogging(const std::string& filename , bool if_overwrite)
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
			s_CoreLogger->info("File logging enabled, view logfile at \".\\{}\"", filename);
		}
		catch (const spdlog::spdlog_ex& ex) {
			s_CoreLogger->error("Failed to enable file logging: {}", ex.what());
		}
	}

	void Log::DisableFileLogging()
	{
		if (s_FileLogger) {
			s_CoreLogger->info("Disabling file logging");
			s_FileLogger->flush();

			// 从核心日志器中移除文件sink | remove file sink from CoreLogger sink
			auto& sinks = s_CoreLogger->sinks();
			if (!sinks.empty() && s_FileLogger) {
				auto file_sink = s_FileLogger->sinks().back();
				sinks.erase(std::remove(sinks.begin(), sinks.end(), file_sink), sinks.end());
			}

			s_FileLogger.reset();
			s_CoreLogger->info("File logging successfully disabled");
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
				s_CoreLogger->warn("Haven't initialize Log yet");
			}
		}
		else {
			std::cout << "[warning] Haven't initialize Log yet" << std::endl;
		}
	}

	inline std::shared_ptr<spdlog::logger>& Log::GetCoreLogger()
	{
		return s_CoreLogger;
	}
	inline std::shared_ptr<spdlog::logger>& Log::GetFileLogger()
	{
		return s_FileLogger;
	}
	inline bool Log::GetInitializeState()
	{
		return s_Initialized;
	}
}

//todo : use marco or sth else to add a (caller):msg type output