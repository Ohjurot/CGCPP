#include "LoggerFactory.h"

void CGCPP::SetupLogging()
{
    auto loggerPtr = spdlog::default_logger()->clone("cgcpp");
    
    loggerPtr->set_pattern("[%d.%m.%Y %H:%M:%S.%e] [%^%l%$] [%n] [%t] %v");
    #ifdef CGCPP_RELEASE
    loggerPtr->set_level(spdlog::level::info);
    #else
    loggerPtr->set_level(spdlog::level::trace);
    #endif

    spdlog::set_default_logger(loggerPtr);
}

CGCPP::Logger CGCPP::GetCreateLogger(const std::string& loggerName)
{
    using namespace std::string_literals;

    const auto compositLoggerName = "cgcpp."s + loggerName;

    auto logger = spdlog::get(compositLoggerName);
    if (!logger)
    {
        logger = spdlog::default_logger()->clone(compositLoggerName);
        spdlog::register_logger(logger);
    }
    return logger;
}
