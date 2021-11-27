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



void MainWindow::on_pushButton_clicked()
{
    connectToBridge();
}

