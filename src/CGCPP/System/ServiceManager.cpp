#include "ServiceManager.h"

void CGCPP::ServiceManager::Start()
{
    if (!m_isRunning)
    {
        for (auto& service : m_service)
        {
            service->Start();
        }

        m_isRunning = true;
    }
}

void CGCPP::ServiceManager::Stop()
{
    if (m_isRunning)
    {
        for (auto& service : m_service)
        {
            service->Stop();
        }
        for (auto& service : m_service)
        {
            service->Await();
        }

        m_isRunning = false;
    }
}
