#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
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

auto handler = std::make_shared<hueplusplus::LinHttpHandler>();
hueplusplus::Bridge bridge("192.168.0.3", 80, "oxSTGUKhgR07uNvaHjNSB-z-gJcweovHiN8ibQ01", handler);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


// Connects to a bridge and returns it.
hue::Bridge connectToBridge()
{
    hue::BridgeFinder finder(std::make_shared<SystemHttpHandler>());

    std::vector<hue::BridgeFinder::BridgeIdentification> bridges = finder.findBridges();

    for (const auto& bridge : bridges)
    {
        //std::cout << "Bridge: " << bridge.mac << " at " << bridge.ip << '\n';
        std::string bip = bridge.ip;
        QString qbip = QString::fromStdString(bip);

        QMessageBox msgBox;
        msgBox.setText(qbip);
        msgBox.exec();
    }
    if (bridges.empty())
    {
        //std::cout << "Found no bridges\n";
        QMessageBox msgBox;
        msgBox.setText("no bridges found");
        msgBox.exec();
        throw std::runtime_error("no bridges found");
    }

    if (macAddress.empty())
    {
        //std::cout << "No bridge given, connecting to first one.\n";
        QMessageBox msgBox;
        msgBox.setText("No bridge given, connecting to first one");
        msgBox.exec();
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
        QMessageBox msgBox;
        msgBox.setText("Given bridge not found");
        msgBox.exec();
       // std::cout << "Given bridge not found\n";
        //throw std::runtime_error("bridge not found");
    }
    return finder.getBridge(*it);
}



void lightsTogle(hue::Bridge& hue, int lightnum)
{
    std::vector<hue::Light> lights = hue.lights().getAll();

    if(lights[lightnum].isOn())
    {
        std::cout << "Turning light " << lightnum << " off";
        lights[lightnum].off();
    }
    else
    {
        std::cout << "Turning light " << lightnum << " on";
        lights[lightnum].on();

    }


    std::cout << "Turned lights back on\n";
}


void MainWindow::on_pushButton_clicked()
{
    hue::Bridge hueB = connectToBridge();
}


void MainWindow::on_pushButton_2_clicked()
{
    lightsTogle(bridge,3);
}

