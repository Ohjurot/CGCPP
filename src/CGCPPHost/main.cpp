#include <CGCPP/Util/LoggerFactory.h>
#include <CGCPP/System/BasicService.h>

class MySvc : public CGCPP::BasicService
{
    public:
        MySvc() : BasicService("mysvc") {}
};

int main()
{
    CGCPP::SetupLogging();

    spdlog::info("App started!");

    MySvc svc;
    svc.Start();
}
