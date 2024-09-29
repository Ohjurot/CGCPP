#pragma once

#include <spdlog/spdlog.h>

#include <memory>
#include <string>

namespace CGCPP
{
    /*!
     * @brief Simple alias for loggers
     */
    using Logger = std::shared_ptr<spdlog::logger>;

    /*!
     * @brief Configures the default logger
     */
    void SetupLogging();
    
    /*!
     * @brief Retrive a loger for a given submodule 
     * 
     * Creates it on demand by cloning the default logger
     * @param loggerName Name of logger to retrive
     * @return Logger pointer
     */
    Logger GetCreateLogger(const std::string& loggerName);

}
