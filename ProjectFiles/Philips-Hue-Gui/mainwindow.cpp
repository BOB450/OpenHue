#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <include/hueplusplus/Bridge.h>
#include <algorithm>
#include <iostream>
#include <include/hueplusplus/LinHttpHandler.h>
#include <include/hueplusplus/Light.h>
#include <include/hueplusplus/BaseDevice.h>
#include <thread>
using namespace std;
using namespace hueplusplus;
namespace hue = hueplusplus;
using SystemHttpHandler = hueplusplus::LinHttpHandler;

// Configure existing connections here, or leave empty for new connection
const std::string macAddress = "";
const std::string username = "";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}
hue::Bridge connectToBridge();//decalre function so that it is defined

void lightsOff(hue::Bridge& hue)
{
    std::vector<hue::Light> lights = hue.lights();

    // Save current on state of the lights
    std::map<int, bool> onMap;
    for (hue::Light& l : lights)
    {
        onMap.emplace(l.getId(), l.isOn());
        l.off();
    }

    // This would be preferrable, but does not work because it also resets the brightness of all lights
    // Group 0 contains all lights, turn all off with a transition of 1 second
    // hue.groups().get(0).setOn(false, 10);
    // -------------------------------------

    std::cout << "Turned off all lights\n";

    std::this_thread::sleep_for(std::chrono::seconds(20));

    // Restore the original state of the lights
    for (hue::Light & l : lights)
    {
        if (onMap[l.getId()])
        {
            l.on();
        }
    }

    std::cout << "Turned lights back on\n";
}

MainWindow::~MainWindow()
{
    delete ui;
    try
    {
        hue::Bridge hue = connectToBridge();

        std::cout << "Connected to bridge. IP: " << hue.getBridgeIP() << ", username: " << hue.getUsername() << '\n';
    }
    catch (...)
    { }

}

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
        bridges.begin(), bridges.end(), [&](const auto & identification) { return identification.mac == macAddress; });
    if (it == bridges.end())
    {
        std::cout << "Given bridge not found\n";
        throw std::runtime_error("bridge not found");
    }
    return finder.getBridge(*it);
}


