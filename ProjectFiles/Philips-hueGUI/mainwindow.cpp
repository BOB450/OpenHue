#include "mainwindow.h"
#include "ui_mainwindow.h"

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

#include <hueplusplus/LinHttpHandler.h>

using SystemHttpHandler = hueplusplus::LinHttpHandler;


namespace hue = hueplusplus;
using namespace std;


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


void MainWindow::on_pushButton_clicked()
{
    auto handler = std::make_shared<hueplusplus::LinHttpHandler>();
    hue::BridgeFinder finder(handler);
    std::vector<hueplusplus::BridgeFinder::BridgeIdentification> bridges = finder.findBridges();
    if (bridges.empty())
    {
        //std::cerr << "No bridges found\n";
        QMessageBox msgBox;
        msgBox.setText("notconnected");
        msgBox.exec();

    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("conected");
        msgBox.exec();
    }
}

