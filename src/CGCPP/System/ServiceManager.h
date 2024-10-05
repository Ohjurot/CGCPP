#pragma once

#include <CGCPP/System/BasicService.h>

#include <memory>
#include <vector>
#include <stdexcept>
#include <type_traits>

namespace CGCPP
{
    /*!
     * @brief Manages services
     */
    class ServiceManager
    {
        public:

            /*!
             * @brief Creates a new service in the container
             * @tparam T Type of the service (must be base on BasicService)
             * @tparam ...Args Type of arguments to construct the service
             * @param ...args Arguments to construct the service
             */
            template<
                typename T, 
                typename... Args, 
                typename = std::enable_if_t<
                    std::is_base_of_v<BasicService, T> && 
                    std::is_constructible_v<T, Args...>
                >
            > 
            void NewService(Args&&... args)
            {
                if (m_isRunning)
                {
                    throw std::logic_error("Can't create services while running");
                }
                m_service.push_back(std::make_unique<T>(std::forward<Args>(args)...));
            }

            /*!
             * @brief Starts the service manager (all services)
             */
            void Start();

            /*!
             * @brief Stops the service manager (all services)
             */
            void Stop();

        private:
            std::vector<std::unique_ptr<BasicService>> m_service;

            bool m_isRunning = false;
    };
}
