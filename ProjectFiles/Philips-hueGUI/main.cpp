#include "mainwindow.h"

#include <QApplication>
#include <hueplusplus/Bridge.h>
#include <hueplusplus/LinHttpHandler.h>
#include <hueplusplus/BaseDevice.h>
#include <hueplusplus/IHttpHandler.h>
#include <hueplusplus/BaseHttpHandler.h>
#include <hueplusplus/LinHttpHandler.h>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <hueplusplus/BridgeConfig.h>
#include <QPushButton>
#include <QMessageBox>

using namespace std;


/*
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
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();


}