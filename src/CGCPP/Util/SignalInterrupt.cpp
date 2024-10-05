#include "SignalInterrupt.h"

void CGCPP::SignalInterrupt::Register()
{
    signal(SIGINT, &SignalHandler);
    #ifdef SIGBREAK // Win32
    signal(SIGBREAK, &SignalHandler);
    #endif
    signal(SIGABRT, &SignalHandler);
    signal(SIGTERM, &SignalHandler);
}

void CGCPP::SignalInterrupt::SoftwareStop()
{
    spdlog::info("Software stop triggerd!");
    s_signalReceived = true;
}

bool CGCPP::SignalInterrupt::CheckSignal(bool clear)
{
    if (s_signalReceived)
    {
        if (clear)
        {
            s_signalReceived = false;
        }
        return true;
    }
    return false;
}

void CGCPP::SignalInterrupt::SignalHandler(int signal)
{
    spdlog::info("Terminate signal received ID={}", signal);
    s_signalReceived = true;
}
