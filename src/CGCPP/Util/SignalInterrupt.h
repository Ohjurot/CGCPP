#pragma once

#include <spdlog/spdlog.h>

#include <csignal>

namespace CGCPP
{
    /*!
     * @brief Listens for interrupts
     */
    class SignalInterrupt
    {
        public:
            /*!
             * @brief Register signals for interrupt events
             */
            static void Register();

            /*!
             * @brief Triggers a CTRL-C Stop by software
             */
            static void SoftwareStop();

            /*!
             * @brief Checks if the signal was received. By default clears it to the not received state
             * @param clear When true clears the internal buffer
             * @return True when signal received otherwise false
             */
            static bool CheckSignal(bool clear = true);

        private:
            /*!
             * @brief Is called when the system receives a registed signal
             * @param siganl ID Of the signal that triggered the function call
             */
            static void SignalHandler(int signal);

        private:
            SignalInterrupt() = delete;
            SignalInterrupt(const SignalInterrupt&) = delete;

            inline static bool s_signalReceived = false;
    };
}
