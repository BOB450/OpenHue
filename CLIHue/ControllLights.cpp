#include <thread>

#include <hueplusplus/Bridge.h>
#include <hueplusplus/BaseDevice.h>
#include <hueplusplus/Light.h>

#ifdef _MSC_VER
#include <hueplusplus/WinHttpHandler.h>

using SystemHttpHandler = hueplusplus::WinHttpHandler;

#else
#include <hueplusplus/LinHttpHandler.h>

using SystemHttpHandler = hueplusplus::LinHttpHandler;

#endif

namespace hue = hueplusplus;

// Configure existing connections here, or leave empty for new connection
const std::string macAddress = "ecb5fa0f4bae";
const std::string username = "oxSTGUKhgR07uNvaHjNSB-z-gJcweovHiN8ibQ01";

// Connects to a bridge and returns it.
hue::Bridge connectToBridge()
{
    hue::BridgeFinder finder(std::make_shared<SystemHttpHandler>());

    std::vector<hue::BridgeFinder::BridgeIdentification> bridges = finder.findBridges();

    for (const auto& bridge : bridges)
    {
        std::cout << "Bridge: " << bridge.mac << " at " << bridge.ip << '\n';
    }
    if (bridges.empty())
    {
        std::cout << "Found no bridges\n";
        throw std::runtime_error("no bridges found");
    }

    if (macAddress.empty())
    {
        std::cout << "No bridge given, connecting to first one.\n";
        return finder.getBridge(bridges.front());
    }
    if (!username.empty())
    {
        finder.addUsername(macAddress, username);
    }
    auto it = std::find_if(
        bridges.begin(), bridges.end(), [&](const auto& identification) { return identification.mac == macAddress; });
    if (it == bridges.end())
    {
        std::cout << "Given bridge not found\n";
        throw std::runtime_error("bridge not found");
    }
    return finder.getBridge(*it);
}


// Turns off the lights on the bridge for 20 seconds. 
// Only turns the lights back on that were on before.
void lightsOff(hue::Bridge& hue)
{
    std::vector<hue::Light> lights = hue.lights().getAll();

    
    lights[1].on();
    lights[4].on();
    lights[3].on();
    lights[2].on();

    std::cout << "Turned off all lights\n";

    std::this_thread::sleep_for(std::chrono::seconds(10));

    lights[4].off();
    lights[3].off();
    lights[2].off();
    lights[5].off();
    lights[6].off();
    lights[7].off();
    lights[8].off();


    std::cout << "Turned lights back on\n";
}



int main(int argc, char** argv)
{

    try
    {
        hue::Bridge hue = connectToBridge();

        std::cout << "Connected to bridge. IP: " << hue.getBridgeIP() << ", username: " << hue.getUsername() << '\n';
        
        lightsOff(hue);
    }
    catch (...)
    { }

    std::cout << "Press enter to exit\n";
    std::cin.get();

    return 0;
}