//utf8
#include "Log.h"

namespace CrystalX
{
	//类内声明的static成员在类外定义需要补充完整作用域

	std::shared_ptr<spdlog::logger> Log::CrstalX_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::CrstalX_ClientLogger;

	void Log::Init()
	{
		//设置日志的输出格式 | Set output format for logger
		spdlog::set_pattern("%^[%T] %n: %v%$");

		//创建日志 | Create CoreLogger and ClientLogger
		CrstalX_CoreLogger = spdlog::stderr_color_mt("CrystalX >> DEBUG");
		CrstalX_CoreLogger->set_level(spdlog::level::trace);

		CrstalX_ClientLogger = spdlog::stderr_color_mt("CrystalX >> RELEASE");
		CrstalX_ClientLogger->set_level(spdlog::level::trace);
	}
}

