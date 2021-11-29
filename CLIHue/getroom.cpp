/**
    \file getroom.cpp
    Copyright Notice\n
    Copyright (C) 2021  BOB450 - developer\n
    This file is part of PhilipsHueGUI.
    PhilipsHueGUI is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    PhilipsHueGUI is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.
    You should have received a copy of the GNU Lesser General Public License
    along with PhilipsHueGUI.  If not, see <http://www.gnu.org/licenses/>.
**/


#include <thread>

#include <hueplusplus/Bridge.h>
#include <hueplusplus/BaseDevice.h>
#include <hueplusplus/Light.h>
#include <hueplusplus/Group.h>

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



std::string getroom(hue::Bridge& hue, int lightnum)
{
    std::vector<hue::Light> lights = hue.lights().getAll(); //gets all lights and adds them to array
    hue::Light light1 = lights[lightnum];//sets the light i to a varible
    std::string room = lights[lightnum].getProductname();
    std::string asd = lights[lightnum].getType();
    int brightness = light1.getBrightness();//uses the light1 instaead of useing lights[lightsnum]

    return room  +"  "+ asd +"  " + std::to_string(brightness);
}



int main(int argc, char** argv)
{
    int i;
    try
    {
        hue::Bridge hue = connectToBridge();
        

        std::cout << "Connected to bridge. IP: " << hue.getBridgeIP() << ", username: " << hue.getUsername() << '\n';
        
        std::cout << "Enter light number :";
        std::cin >> i;
       std::cout << getroom(hue,i);
        
    }
    catch (...)
    { }

    //std::cout << "Press enter to exit\n";
    std::cin.get();

    return 0;
}