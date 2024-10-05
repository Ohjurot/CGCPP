#include "BasicService.h"

CGCPP::BasicService::BasicService(std::string_view name) :
    m_name(name)
{
    m_logger = GetCreateLogger(m_name);
}

CGCPP::BasicService::~BasicService()
{
    Stop();
    Await();
}

void CGCPP::BasicService::Start()
{
    if (!m_runFlag.test_and_set(std::memory_order_acquire))
    {
        m_workThread = boost::thread(&BasicService::ThreadMain, this);
    }
}

void CGCPP::BasicService::Stop()
{
    if (!m_stopFlag)
    {
        OnStop();
        m_stopFlag = true;
    }
}

void CGCPP::BasicService::Await()
{
    while (m_runFlag.test())
    {
        std::this_thread::yield();
    }
}

void CGCPP::BasicService::ThreadMain()
{
    using namespace std::chrono_literals;

    GetLogger()->info("Service thread started");

    OnStart();

    auto lastTick = clock::now();
    while (!m_stopFlag)
    {
        auto now = clock::now();
        OnUpdate(std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTick).count());
        lastTick = now;

        std::this_thread::sleep_for(1ms);
    }

    OnTerminate();

    GetLogger()->info("Service thread stopped");
    m_runFlag.clear(std::memory_order_release);
}
