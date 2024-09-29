#pragma once

#include <CGCPP/Util/LoggerFactory.h>

#include <boost/thread.hpp>

#include <string>
#include <atomic>
#include <thread>
#include <string_view>

namespace CGCPP
{
    /*!
     * @brief Base class for all service
     */
    class BasicService
    {
        public:
            BasicService(std::string_view name);
            ~BasicService();

            /*!
             * @brief Starts the service
             */
            void Start();

            /*!
             * @brief Stops the service
             */
            void Stop();

            /*!
             * @brief Awits the service termination
             */
            void Await();

        protected:
            /*!
             * @brief 
             * @return Copy of logger 
             */
            inline const Logger& GetLogger() const { return m_logger; }

        private:
            /*!
             * @brief Runs the async code
             */
            void ThreadMain();

        private:
            /*!
             * @brief Name of the service
             */
            const std::string m_name;

            /*!
             * @brief Logger pointer
             */
            Logger m_logger;

            /*!
             * @brief While set is running
             */
            std::atomic_flag m_runFlag;

            /*!
             * @brief When set the service shall terminate
             */
            bool m_stopFlag = false;

            /*!
             * @brief Actual thread that executes the work
             */
            boost::thread m_workThread;
    };
}
