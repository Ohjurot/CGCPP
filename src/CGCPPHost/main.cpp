#include <CGCPP/Util/LoggerFactory.h>
#include <CGCPP/Util/SignalInterrupt.h>
#include <CGCPP/System/BasicService.h>
#include <CGCPP/System/ServiceManager.h>

#include <httplib.h>

const char* HTLM =
R"(
<!doctype html>
<html lang="en" data-bs-theme="dark">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Bootstrap demo</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-QWTKZyjpPEjISv5WaRU9OFeRpok6YctnYmDr5pNlyT2bRjXh0JMhjY6hW+ALEwIH" crossorigin="anonymous">
  </head>
  <body>
    <h1>Hello, world!</h1>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz" crossorigin="anonymous"></script>
  </body>
</html>
)";

class WWWService : public CGCPP::BasicService
{
    public:
        WWWService() : BasicService("www")
        {
            m_server.Get("/",
                [&](const httplib::Request& request, httplib::Response& response)
                {
                    response.set_content(HTLM, "text/html");
                }
            );

            m_server.bind_to_port("0.0.0.0", 80);
        }

    protected:
        void OnStart() override 
        {
            if (!m_server.listen_after_bind())
            {
                GetLogger()->error("Failed to start HTTP server!");
                CGCPP::SignalInterrupt::SoftwareStop();
            }
        }

        void OnStop() override 
        { 
            m_server.stop();
        }

    private:
        httplib::Server m_server;
};

int main()
{
    using namespace std::chrono_literals;

    CGCPP::SetupLogging();
    CGCPP::SignalInterrupt::Register();

    spdlog::info("App started!");

    CGCPP::ServiceManager services;
    services.NewService<WWWService>();

    services.Start();

    while (!CGCPP::SignalInterrupt::CheckSignal())
    {
        std::this_thread::sleep_for(100ms);
    }

    services.Stop();
}
