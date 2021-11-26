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
void lightsOff(hue::Bridge& hue,int o, int lightnum, hue::RGB c)
{
    std::vector<hue::Light> lights = hue.lights().getAll();

    if(o == 0)
    {
        std::cout << "Turning light " << lightnum << " off";
        lights[lightnum].off();
    }
    else
    {
        std::cout << "Turning light " << lightnum << " on";
        lights[lightnum].on();
        lights[lightnum].setColorRGB(c);
    }


    std::cout << "Turned lights back on\n";
}



int main(int argc, char** argv)
{
    int i;
    int r,g,b;
    int onoff;
    try
    {
        hue::Bridge hue = connectToBridge();
        

        std::cout << "Connected to bridge. IP: " << hue.getBridgeIP() << ", username: " << hue.getUsername() << '\n';
        
        std::cout << "what light would you want to toggle :";
        std::cin >> i;
        std::cout << "do you want to turn on(1) or off(0)";
        std::cin >> onoff;
        std::cout << "enter the color of the light ex. r:13 g:160 b:255";
        std::cin >> r;
        std::cin >> g;
        std::cin >> b;
        hue::RGB color = {r,g,b};
        lightsOff(hue,onoff,i,color);
    }
    catch (...)
    { }

    std::cout << "Press enter to exit\n";
    std::cin.get();

    return 0;
}