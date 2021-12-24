/**
    \file mainwindow.cpp
    Copyright Notice\n
    Copyright (C) 2021  BOB450 - developer\n
    This file is part of OpenHue.
    OpenHue is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    OpenHue is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.
    You should have received a copy of the GNU Lesser General Public License
    along with OpenHue.  If not, see <http://www.gnu.org/licenses/>.
**/


#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "customitem.h"
#include "groupitem.h"
#include <string>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <thread>
#include <QListWidget>
#include <QListWidgetItem>
#include <QColorDialog>
#include <QColor>
#include <QSettings>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>

#include <hueplusplus/Bridge.h>
#include <hueplusplus/BaseDevice.h>
#include <hueplusplus/Light.h>
#include <hueplusplus/ColorHueStrategy.h>

#ifdef _MSC_VER
#include <hueplusplus/WinHttpHandler.h>

using SystemHttpHandler = hueplusplus::WinHttpHandler;

#else
#include <hueplusplus/LinHttpHandler.h>

using SystemHttpHandler = hueplusplus::LinHttpHandler;

#endif

namespace hue = hueplusplus;

hue::Bridge connectToBridge();

// Configure existing connections here, or leave empty for new connection
 int port;
 QString username = "";
 QString ipAddress = "";

 bool cleared = false;
 bool hascleared = false;

 bool RoomView = false;


// pre made connection will not be used for final product
auto handler = std::make_shared<hueplusplus::LinHttpHandler>();//linhttphandler is only for linux
hueplusplus::Bridge bridge(ipAddress.toStdString(), port, username.toStdString(), handler);

//check bridge connection
bool MainWindow::isBridgeVisible()
{
     QSettings connectionVal("OpenHue","BOB450"); //gets or makes a settings file
     ipAddress = connectionVal.value("bridgeIP").toString();

    QStringList parameters;
    QStringList parameters2;
 #if defined(WIN32)
    parameters << "-n" << "1";
 #else
    parameters << "-c 1";
 #endif

    parameters << ipAddress;

    int exitCode = QProcess::execute("ping", parameters);
    if (exitCode==0) {
        // it's alive
        return true;
    } else {
        parameters2 << "google.com";
        int exitCode2 = QProcess::execute("ping", parameters2);
        if(exitCode==0)
        {
            return true;
        }
        else{
        // it's dead
        return false;}
    }
}

void MainWindow::setLightIndacator(CustomItem* i, QString qs)//sets light indacator based on passed in rgb value
{
   // QString sr = QString::number(r);
    //QString sg = QString::number(g);
    //QString sb = QString::number(b);
    //QString backgroundc = sr + "," + sg + "," + sb;
   // QString first = "QFrame#frame { background-color: rgb(";
    //QString last = "); border: 2px solid black; border-radius: 10px; padding: 2px; }";
    //QString style1 = first + qs + last;
    i->setStyleSheet("QFrame#frame { background-color: rgb(12,12,222); border: 2px solid black; border-radius: 10px; padding: 2px; }");

}

QString MainWindow::GetLightColor(hue::Light i)//will return color
{
    if(i.hasColorControl()){

    hue::XYBrightness icolor = i.getColorXY();
    hue::RGB rgb;
    rgb = rgb.fromXY(icolor);
    int r,g,b;
    r = rgb.r;
    g = rgb.g;
    b = rgb.b;
    //QMessageBox msgBox;

    return QString::number(r) + "," + QString::number(g) + "," + QString::number(b);
    //msgBox.exec();

    }
    else
    {

    }


}

void MainWindow::checkConnection()//checks on startup if there is a pre esablished connection and if not then make one.
{
    if(MainWindow::isBridgeVisible() == false)
    {
        QMessageBox msgBox;
        msgBox.setText("Your not connected to the internet!");
        msgBox.exec();

    }
    else
    {
    QSettings connectionVal("OpenHue","BOB450"); //gets or makes a settings file

    if(connectionVal.value("bridgeIP").isNull())//if a bridge has not been saved to settings
    {
        QMessageBox msgBox;

        msgBox.setText("click ok then go and push the button on your hue bridge you have 35 seconds");
        msgBox.exec();

        hue::Bridge B = connectToBridge();

        //sets all nessasary to disk
        QVariant QBridgeIP = QString::fromStdString(B.getBridgeIP());
        connectionVal.setValue("bridgeIP", QBridgeIP);
        int port = B.getBridgePort();
        connectionVal.setValue("bridgePort", port);
        QVariant QBridgeUsername = QString::fromStdString(B.getUsername());
        connectionVal.setValue("bridgeUsername", QBridgeUsername);

        //get values from connecttionValue and set to varibles to pas into line 59
        port = connectionVal.value("bridgePort").toInt();
        username = connectionVal.value("bridgeUsername").toString();
        ipAddress = connectionVal.value("bridgeIP").toString();

    }
    if(connectionVal.value("bridgeIP").isNull() == false)//if there is a bridge connection saved
    {

        port = connectionVal.value("bridgePort").toInt();
        username = connectionVal.value("bridgeUsername").toString();
        ipAddress = connectionVal.value("bridgeIP").toString();

       // hueplusplus::Bridge bridge(ipAddress.toStdString(), port, username.toStdString(), handler);

        QMessageBox msgBox2;

        msgBox2.setText("Bridge info: " + username + "  " + ipAddress);
        msgBox2.exec();
        //get values from connecttionValue and set to varibles to pas into line 59
    }

    //settings.setValue("editor/wrapMargin", 68);
    }

}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    if(MainWindow::isBridgeVisible() == false)
    {
        QMessageBox msgBox;
        msgBox.setText("Your not connected to the internet! Please connect and restart.");
        msgBox.exec();
        MainWindow::on_actionDelete_triggered();
        QApplication::quit();
    }
    else
    {

    ui->setupUi(this);
    //ui->listWidget->setStyleSheet("QListWidget{border: 2px solid black; border-radius: 5px; }");
    checkConnection(); //runs after the application has started up.
    on_actionRefresh_lights_triggered();

    }


}


MainWindow::~MainWindow()
{
    delete ui;// runs when program exits.

}


// Connects to a bridge and returns it user needs to push button for this.
hue::Bridge connectToBridge()
{
    // For windows use std::make_shared<hueplusplus::WinHttpHandler>();
    auto handler = std::make_shared<hueplusplus::LinHttpHandler>();
    hueplusplus::BridgeFinder finder(handler);
    std::vector<hueplusplus::BridgeFinder::BridgeIdentification> bridges = finder.findBridges();
    if (bridges.empty())
    {
        //std::cerr << "No bridges found\n";
          QMessageBox msgBox;

          msgBox.setText("No bridges found");
          msgBox.exec();

    }
    else
    {
        //QMessageBox msgBox2;
        //msgBox2.setText("Go push the button on the hue bridge you have 30 seconds");
        //msgBox2.exec();
         hueplusplus::Bridge bridgeF = finder.getBridge(bridges[0]);// user needts to push bitton on bridge now to athenticate


         std::string BFip = bridgeF.getBridgeIP();
         int BFport = bridgeF.getBridgePort();
         std::string BFportS = std::to_string(BFport);
         std::string BFkey = bridgeF.getClientKey();
         std::string BFusername = bridgeF.getUsername();

           QMessageBox msgBox;

           msgBox.setText(QString::fromStdString("ip: " + BFip + "   Port: " + BFportS + "    key: " + BFkey + "    username: " + BFusername));
           msgBox.exec();
         return bridgeF;
    }
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
//gets all lights and adds to array
std::vector<hue::Light> getLight(hue::Bridge& hue)
{
    std::vector<hue::Light> lights = hue.lights().getAll();
    return lights;

}


// Adds lights to the list wigit by looping though all the lights and adding each by there name.


// Togles selected light by getting selected list item then looping through all lights and checking
// if the names match if they do then check if light if so then turn on if not then turn off.
void MainWindow::togleLights()
{
    hueplusplus::Bridge bridge(ipAddress.toStdString(), port, username.toStdString(), handler);
    if(!ui->listWidget->selectedItems().empty()){//check if a light is selected if not then dont do anything fixes crash.
    if(RoomView == false){
  // QString text = ui->listWidget->currentItem()->text();
        auto item = ui->listWidget->currentItem();//get current item selected
        auto itemWidget = dynamic_cast<CustomItem*>(ui->listWidget->itemWidget(item));//get custom item from selected item
     QString text = itemWidget->getText();//retrive item text

    std::vector<hue::Light> allLights = getLight(bridge);
    int Lsize =  allLights.size();
    for(int i = 0; i < Lsize; i++)
    {
        QString qlight = QString::fromStdString(allLights[i].getName());

        if(qlight == text)
        {
            if(allLights[i].isOn())
            {
                allLights[i].off();
            }
            else
            {
                allLights[i].on();
            }
        }
    }
    }
    else
    {
        //QString text1 = ui->listWidget->currentItem()->text();
        auto item = ui->listWidget->currentItem();//get current item selected
        auto itemWidget = dynamic_cast<GroupItem*>(ui->listWidget->itemWidget(item));//get custom item from selected item
     QString text1 = itemWidget->getText();//retrive item text

        std::vector<hue::Group> groups = bridge.groups().getAll();
        int Lsize =  groups.size();
         for(int i = 0; i < Lsize; i++)
         {
             QString qroom = QString::fromStdString(groups[i].getName());

             if(qroom == text1)
             {
                 if(groups[i].getAllOn())
                 {
                     groups[i].setOn(false);
                 }
                 else
                 {
                     groups[i].setOn(true);
                 }
             }
         }
    }
    }
    else
    {
        QMessageBox msgBox;

        msgBox.setText("Select a light/Room");
        msgBox.exec();
    }
}


void MainWindow::on_pushButton_4_clicked()//togle light button
{
    if(MainWindow::isBridgeVisible() == false)
    {
        QMessageBox msgBox;
        msgBox.setText("Your not connected to the internet!");
        msgBox.exec();
    }
    else{
    QFuture<void> i = QtConcurrent::run(&MainWindow::togleLights,this);
    }
}

void MainWindow::ChangeLightColor()
{
    hueplusplus::Bridge bridge(ipAddress.toStdString(), port, username.toStdString(), handler);
    if(!ui->listWidget->selectedItems().empty()){//check if a light is selected if not then dont do anything fixes crash.

    if(RoomView == false){

    //QString text = ui->listWidget->currentItem()->text();
        auto item = ui->listWidget->currentItem();//get current item selected
        auto itemWidget = dynamic_cast<CustomItem*>(ui->listWidget->itemWidget(item));//get custom item from selected item
     QString text = itemWidget->getText();//retrive item text

     std::vector<hue::Light> allLights = getLight(bridge);
     int Lsize =  allLights.size();
     for(int i = 0; i < Lsize; i++)
     {
         QString qlight = QString::fromStdString(allLights[i].getName());

         if(qlight == text)
         {
             if(allLights[i].hasColorControl()){
             QColor color = QColorDialog::getColor(Qt::white,this,"chose color");
             if(color.isValid())
             {


                 int r = color.red();
                 int g = color.green();
                 int b = color.blue();
                /* QString rq = QString::number(r);
                 QString gq = QString::number(g);
                 QString bq = QString::number(b);
                 QMessageBox msgBox;

                 msgBox.setText(rq +" "+ gq +" "+ bq);
                 msgBox.exec();
                 */

                 hue::RGB huecolor = {r,g,b}; //wierd error not important
                 allLights[i].setColorRGB(huecolor);
             }
             else
             {
                    QMessageBox msgBox;

                    msgBox.setText("Chose a valid color");
                    msgBox.exec();
             }
             }
             else
             {
                 QMessageBox msgBox;

                 msgBox.setText("This light dose not support color");
                 msgBox.exec();
             }

         }
     }

     MainWindow::on_actionRefresh_lights_triggered();
    }
    else
    {
        //std::vector<hue::Bridge::GroupList> groups = bridge.groups().get();
        std::vector<hue::Group> groups = bridge.groups().getAll();
        int Lsize =  groups.size();
      //  QMessageBox msgBox;
      //   QString qlight = QString::fromStdString(groups[1].getName());
       // msgBox.setText(qlight);
       // msgBox.exec();

       //QString textg = ui->listWidget->currentItem()->text();

        auto item = ui->listWidget->currentItem();//get current item selected
        auto itemWidget = dynamic_cast<GroupItem*>(ui->listWidget->itemWidget(item));//get custom item from selected item
     QString textg = itemWidget->getText();//retrive item text

        for(int i = 0; i < Lsize; i++)
        {
            QString qroom = QString::fromStdString(groups[i].getName());
            if(qroom == textg)
            {
                QColor colorg = QColorDialog::getColor(Qt::white,this,"chose color");
                if(colorg.isValid())
                {


                    int r = colorg.red();
                    int g = colorg.green();
                    int b = colorg.blue();
                   /* QString rq = QString::number(r);
                    QString gq = QString::number(g);
                    QString bq = QString::number(b);
                    QMessageBox msgBox;

                    msgBox.setText(rq +" "+ gq +" "+ bq);
                    msgBox.exec();
                    */

                    hue::RGB huecolor1 = {r,g,b}; //wierd error not important

                    groups[i].setColor(huecolor1.toXY());
                }
                else
                {
                       QMessageBox msgBox;

                       msgBox.setText("Chose a valid color");
                       msgBox.exec();
                }
            }


        }
    }
    }
    else
    {
        QMessageBox msgBox;

        msgBox.setText("Select a light/Room");
        msgBox.exec();
    }
}


void MainWindow::on_pushButton_5_clicked() //change color of selected light
{
    if(MainWindow::isBridgeVisible() == false)
    {
        QMessageBox msgBox;
        msgBox.setText("Your not connected to the internet!");
        msgBox.exec();
    }
    else{
    QFuture<void> i = QtConcurrent::run(&MainWindow::ChangeLightColor,this);
    i.waitForFinished();
    }

}


void MainWindow::on_horizontalSlider_rangeChanged(int min, int max) //not in use
{
  //  int ipos = ui->horizontalSlider->sliderPosition();
   // QString pos = QString::number(ipos);
   // QMessageBox msgBox;

   // msgBox.setText(pos);
   // msgBox.exec();
}


void MainWindow::on_horizontalSlider_valueChanged(int value) //gets called evrytim the slider changes not when the user stops sliding so it is not fluid
{
    /*
    int ipos = ui->horizontalSlider->sliderPosition();

   // QString pos = QString::number(ipos);
   // QMessageBox msgBox;

    //msgBox.setText(pos);
    //msgBox.exec();
    QString text = ui->listWidget->currentItem()->text();
     std::vector<hue::Light> allLights = getLight(bridge);
     int Lsize =  allLights.size();
     for(int i = 0; i < Lsize; i++)
     {
         QString qlight = QString::fromStdString(allLights[i].getName());
         if(qlight == text)
         {


            allLights[i].setBrightness(ipos);
         }
     }
     */
}


void MainWindow::changeBrightness()
{
    hueplusplus::Bridge bridge(ipAddress.toStdString(), port, username.toStdString(), handler);
    if(!ui->listWidget->selectedItems().empty()){//check if a light is selected if not then dont do anything fixes crash.
    int ipos = ui->horizontalSlider->sliderPosition();
    if(RoomView == false){
   // QString pos = QString::number(ipos);
   // QMessageBox msgBox;

    //msgBox.setText(pos);
    //msgBox.exec();
   // QString text = ui->listWidget->currentItem()->text();
        auto item = ui->listWidget->currentItem();//get current item selected
        auto itemWidget = dynamic_cast<CustomItem*>(ui->listWidget->itemWidget(item));//get custom item from selected item
     QString text = itemWidget->getText();//retrive item text

     std::vector<hue::Light> allLights = getLight(bridge);
     int Lsize =  allLights.size();
     for(int i = 0; i < Lsize; i++)
     {
         QString qlight = QString::fromStdString(allLights[i].getName());
         if(qlight == text)
         {
            if(allLights[i].hasBrightnessControl())
            {

            allLights[i].setBrightness(ipos);
            }
            else
            {

                 QMessageBox msgBox;

                 msgBox.setText("this light dose not have brightness support.");
                 msgBox.exec();
            }
         }
     }
    }
    else
    {
        //QString text2 = ui->listWidget->currentItem()->text();
        auto item = ui->listWidget->currentItem();//get current item selected
        auto itemWidget = dynamic_cast<GroupItem*>(ui->listWidget->itemWidget(item));//get custom item from selected item
     QString text2 = itemWidget->getText();//retrive item text

        std::vector<hue::Group> groups = bridge.groups().getAll();
        int Lsize =  groups.size();
         for(int i = 0; i < Lsize; i++)
         {
             QString qlight = QString::fromStdString(groups[i].getName());
             if(qlight == text2)
             {


                groups[i].setBrightness(ipos);

             }
         }
    }
    }
    else
    {
        QMessageBox msgBox;

        msgBox.setText("Select a light/Room");
        msgBox.exec();
    }
}

void MainWindow::on_horizontalSlider_sliderReleased()//change brightness button
{
    if(MainWindow::isBridgeVisible() == false)
    {
        QMessageBox msgBox;
        msgBox.setText("Your not connected to the internet!");
        msgBox.exec();
    }
    else{
    QFuture<void> i3 = QtConcurrent::run(&MainWindow::changeBrightness,this);
    }
}


void MainWindow::on_listWidget_itemPressed(QListWidgetItem *item)
{

}

void MainWindow::itemClicked()
{
    hueplusplus::Bridge bridge(ipAddress.toStdString(), port, username.toStdString(), handler);
    if(!RoomView){

    //QString text = ui->listWidget->currentItem()->text();
    auto item = ui->listWidget->currentItem();//get current item selected
    auto itemWidget = dynamic_cast<CustomItem*>(ui->listWidget->itemWidget(item));//get custom item from selected item
 QString text = itemWidget->getText();//retrive item text

     std::vector<hue::Light> allLights = getLight(bridge);
     int Lsize =  allLights.size();
     for(int i = 0; i < Lsize; i++)
     {
         QString qlight = QString::fromStdString(allLights[i].getName());
         if(qlight == text)
         {
             if(!allLights[i].hasTemperatureControl())
             {
                 ui->horizontalSlider_2->hide();
             }
             else
             {
                 ui->horizontalSlider_2->setHidden(false);
             }
             if(!allLights[i].hasBrightnessControl())
             {
                 ui->horizontalSlider->hide();
             }
             else
             {
                 ui->horizontalSlider->setHidden(false);
             }

            int bri = allLights[i].getBrightness(); // get brightness from light
            ui->horizontalSlider->setValue(bri); // set position of slider to that of the selected light
            int Ctemp = allLights[i].getColorTemperature(); // get color temp from light
            ui->horizontalSlider_2->setValue(Ctemp);
         }
     }
    }
    else{
        //QString text = ui->listWidget->currentItem()->text();
        auto item = ui->listWidget->currentItem();//get current item selected
        auto itemWidget = dynamic_cast<GroupItem*>(ui->listWidget->itemWidget(item));//get custom item from selected item
     QString text = itemWidget->getText();//retrive item text

         std::vector<hue::Light> allLights = getLight(bridge);
         int Lsize =  allLights.size();
         for(int i = 0; i < Lsize; i++)
         {
             QString qlight = QString::fromStdString(allLights[i].getName());
             if(qlight == text)
             {
                 if(!allLights[i].hasTemperatureControl())
                 {
                     ui->horizontalSlider_2->hide();
                 }
                 else
                 {
                     ui->horizontalSlider_2->setHidden(false);
                 }
                 if(!allLights[i].hasBrightnessControl())
                 {
                     ui->horizontalSlider->hide();
                 }
                 else
                 {
                     ui->horizontalSlider->setHidden(false);
                 }

                int bri = allLights[i].getBrightness(); // get brightness from light
                ui->horizontalSlider->setValue(bri); // set position of slider to that of the selected light
                int Ctemp = allLights[i].getColorTemperature(); // get color temp from light
                ui->horizontalSlider_2->setValue(Ctemp);
             }
         }

    }
}

//When a light is clicked set the britness of the light eqal to the slider
void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QFuture<void> i3 = QtConcurrent::run(&MainWindow::itemClicked,this);
}


void MainWindow::on_listWidget_itemSelectionChanged()
{

}

//When a light is double cliked or enter is pressed set the britness of the light eqal to the slider
void MainWindow::on_listWidget_itemActivated(QListWidgetItem *item)
{
    QFuture<void> i3 = QtConcurrent::run(&MainWindow::itemClicked,this);
}

void MainWindow::sliderWarmth()
{
    hueplusplus::Bridge bridge(ipAddress.toStdString(), port, username.toStdString(), handler);
    if(!ui->listWidget->selectedItems().empty()){
    int ipos = ui->horizontalSlider_2->sliderPosition();
    if(RoomView == false){
   // QString pos = QString::number(ipos);
   // QMessageBox msgBox;

    //msgBox.setText(pos);
    //msgBox.exec();
    //QString text = ui->listWidget->currentItem()->text();
        auto item = ui->listWidget->currentItem();//get current item selected
        auto itemWidget = dynamic_cast<CustomItem*>(ui->listWidget->itemWidget(item));//get custom item from selected item
     QString text = itemWidget->getText();//retrive item text

     std::vector<hue::Light> allLights = getLight(bridge);
     int Lsize =  allLights.size();
     for(int i = 0; i < Lsize; i++)
     {
         QString qlight = QString::fromStdString(allLights[i].getName());
         if(qlight == text)
         {
             if(allLights[i].hasTemperatureControl())
             {
            // int z = allLights[i].getColorTemperature();
             //QString tempt = QString::number(z);
              //QMessageBox msgBox;

              //msgBox.setText(tempt);
              //msgBox.exec();

            allLights[i].setColorTemperature(ipos);
            }
             else
             {

                  QMessageBox msgBox;

                  msgBox.setText("This light dose not have tempreture controll");
                  msgBox.exec();
             }
         }
     }
    }
    else
    {
       // QString text2 = ui->listWidget->currentItem()->text();
        auto item = ui->listWidget->currentItem();//get current item selected
        auto itemWidget = dynamic_cast<GroupItem*>(ui->listWidget->itemWidget(item));//get custom item from selected item
     QString text2 = itemWidget->getText();//retrive item text

        std::vector<hue::Group> groups = bridge.groups().getAll();
        int Lsize =  groups.size();
         for(int i = 0; i < Lsize; i++)
         {
             QString qlight = QString::fromStdString(groups[i].getName());
             if(qlight == text2)
             {

                groups[i].setColorTemperature(ipos);

             }
         }
    }
    }
    else
    {
        QMessageBox msgBox;

        msgBox.setText("Select a light/Room");
        msgBox.exec();
    }
}

//slider for warmth of light
void MainWindow::on_horizontalSlider_2_sliderReleased()
{    if(MainWindow::isBridgeVisible() == false)
    {
        QMessageBox msgBox;
        msgBox.setText("Your not connected to the internet!");
        msgBox.exec();
    }
    else{
    QFuture<void> i = QtConcurrent::run(&MainWindow::sliderWarmth,this);
    }
}

void MainWindow::ItemListArrowKeys()
{
    if(cleared == false)//if lights have been cleared do not run becuase it will cuase crash
    {
    hueplusplus::Bridge bridge(ipAddress.toStdString(), port, username.toStdString(), handler);

    QString text;
    if(RoomView){ui->horizontalSlider->setHidden(false); ui->horizontalSlider_2->setHidden(false);
        // QString text = ui->listWidget->currentItem()->text();
         auto item = ui->listWidget->currentItem();//get current item selected
         auto itemWidget = dynamic_cast<GroupItem*>(ui->listWidget->itemWidget(item));//get custom item from selected item
      QString text = itemWidget->getText();//retrive item text
    }
    else
    {
        // QString text = ui->listWidget->currentItem()->text();
         auto item = ui->listWidget->currentItem();//get current item selected
         auto itemWidget = dynamic_cast<CustomItem*>(ui->listWidget->itemWidget(item));//get custom item from selected item
      QString text = itemWidget->getText();//retrive item text
    }

     std::vector<hue::Light> allLights = getLight(bridge);
     int Lsize =  allLights.size();
     for(int i = 0; i < Lsize; i++)
     {
         QString qlight = QString::fromStdString(allLights[i].getName());
         if(qlight == text)
         {
            if(!allLights[i].hasTemperatureControl())
            {
                ui->horizontalSlider_2->hide();
            }
            else
            {
                ui->horizontalSlider_2->setHidden(false);
            }
            if(!allLights[i].hasBrightnessControl())
            {
                ui->horizontalSlider->hide();
            }
            else
            {
                ui->horizontalSlider->setHidden(false);
            }

            int bri = allLights[i].getBrightness(); // get brightness from light
            ui->horizontalSlider->setValue(bri); // set position of slider to that of the selected light
            int Ctemp = allLights[i].getColorTemperature(); // get color temp from light
            ui->horizontalSlider_2->setValue(Ctemp);
         }
     }
    }
    else
    {
        hascleared = true;
        cleared = false;
    }
}

// When you change a item using arrow keys or sutch it will now update the sliders.
void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QFuture<void> i = QtConcurrent::run(&MainWindow::ItemListArrowKeys,this);
}


void MainWindow::on_actionRefresh_lights_triggered()// Adds lights to the list wigit by looping though all the lights and adding each by there name.

{
    if(MainWindow::isBridgeVisible() == false)
    {
        QMessageBox msgBox;
        msgBox.setText("Your not connected to the internet!");
        msgBox.exec();
    }
    else{
    cleared = true;
    RoomView = false;

    hueplusplus::Bridge bridge(ipAddress.toStdString(), port, username.toStdString(), handler);
    std::vector<hue::Light> allLights = getLight(bridge);
    int Lsize =  allLights.size();
 //   QMessageBox msgBox;
   //  QString qlight = QString::fromStdString(allLights[1].getName());
   // msgBox.setText(qlight);
   // msgBox.exec();

        ui->listWidget->clear();

    for(int i = 0; i < Lsize; i++)
    {
        QString qlight = QString::fromStdString(allLights[i].getName());



        auto item = new QListWidgetItem();

        auto widget = new CustomItem(this);
        widget->setText(qlight);
       // widget->setStyleSheet("background-color: rgb(13,40,70);");
        //widget->setStyleSheet("QFrame#frame { background-color: rgb(120,12,12); border: 2px solid black; border-radius: 10px; padding: 2px; }");
       // MainWindow::setLightIndacator(widget,MainWindow::GetLightColor(allLights[i]));

        //update light indacator
        if(allLights[i].hasTemperatureControl()){

        hue::XYBrightness icolor = allLights[i].getColorXY();
        hue::RGB rgb;
        rgb = rgb.fromXY(icolor);
        int r,g,b;
        r = rgb.r;
        g = rgb.g;
        b = rgb.b;
        //QMessageBox msgBox;

        QString qwe =  QString::number(r) + "," + QString::number(g) + "," + QString::number(b);
        if(allLights[i].isOn()){
         widget->setStyleSheet("QFrame#frame { background-color: rgb("+ qwe + "); border: 2px solid black; border-radius: 10px; padding: 2px; } QFrame#frame_2 {border: 2px solid black; border-radius: 10px; padding: 2px; background-color: white;}");
        }
        else
        {
            widget->setStyleSheet("QFrame#frame { background-color: rgb("+ qwe + "); border: 2px solid black; border-radius: 10px; padding: 2px; } QFrame#frame_2 {border: 2px solid black; border-radius: 10px; padding: 2px;  background-color: black;}");
        }
        //msgBox.exec();

        }
        else
        {
            if(allLights[i].isOn()){
            widget->setStyleSheet("QFrame#frame_2 {border: 2px solid black; border-radius: 10px; padding: 2px; background-color: white;}");
            }
            else{
                widget->setStyleSheet("QFrame#frame_2 {border: 2px solid black; border-radius: 10px; padding: 2px; background-color: black;}");
            }
        }



        item->setSizeHint(widget->sizeHint());

        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, widget);

       // ui->listWidget->addItem(qlight);
    }
}

}


void MainWindow::on_actionRefresh_Bridge_Connection_triggered()//menu bar calls funtion to reconnect to bridge
{
    checkConnection();
}


void MainWindow::on_actionCredits_triggered()
{
       QMessageBox msgBox;

       msgBox.setText("Main Devloper: BOB450 using blank hue library");
       msgBox.exec();
}


void MainWindow::on_actionSource_Code_triggered()
{
    QMessageBox msgBox;


    msgBox.setText("Source code: <a href='https://github.com/BOB450/OpenHue'>Github</a>");
    msgBox.exec();
}









void MainWindow::on_actionLights_triggered()
{
    on_actionRefresh_lights_triggered();// Adds light to list hense switch back to light view
}


void MainWindow::on_actionRoom_Group_triggered()
{
    if(MainWindow::isBridgeVisible() == false)
    {
        QMessageBox msgBox;
        msgBox.setText("Your not connected to the internet!");
        msgBox.exec();
    }
    else{
    RoomView = true;
    cleared = true;//to stop proam from crashing
    hueplusplus::Bridge bridge(ipAddress.toStdString(), port, username.toStdString(), handler);
    //std::vector<hue::Bridge::GroupList> groups = bridge.groups().get();
    std::vector<hue::Group> groups = bridge.groups().getAll();
    int Lsize =  groups.size();
  //  QMessageBox msgBox;
  //   QString qlight = QString::fromStdString(groups[1].getName());
   // msgBox.setText(qlight);
   // msgBox.exec();

    ui->listWidget->clear();

    for(int i = 0; i < Lsize; i++)
    {
        QString qroom = QString::fromStdString(groups[i].getName());
        auto item = new QListWidgetItem();

        auto widget = new GroupItem(this);
        widget->setText(qroom);

        item->setSizeHint(widget->sizeHint());

      //  widget->setStyleSheet("QFrame#frame {border: 2px solid black; border-radius: 10px; padding: 2px; }");

        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, widget);

       // ui->listWidget->addItem(qroom);
    }
    //std::string i = bridge.groups().getAll();
    }
}


void MainWindow::on_actionRefresh_Rooms_Groups_triggered()//refresh group in menu bar
{
    on_actionRoom_Group_triggered();
}


void MainWindow::on_actionBridge_Info_triggered()
{
    QMessageBox msgBox2;

    msgBox2.setText("Bridge info:   " + username + "   Bridge ip:   " + ipAddress + "   Port:  " + QString::fromStdString(std::to_string(port)));
    msgBox2.exec();
}


void MainWindow::on_actionBug_Report_triggered()
{
    QMessageBox msgBox;


    msgBox.setText("Report bug,issue or feature request here: <a href='https://github.com/BOB450/OpenHue/issues/new/choose'>Github</a>");
    msgBox.exec();
}


void MainWindow::on_actionDelete_triggered()
{
    if(MainWindow::isBridgeVisible() == false)
    {
        QMessageBox msgBox;
        msgBox.setText("Your not connected to the internet!");
        msgBox.exec();
    }
    else
    {
    QSettings connectionVal("OpenHue","BOB450"); //gets or makes a settings file
    QMessageBox msgBox;
    msgBox.setText("Bridge connection Deleted. Making new connection");
    msgBox.exec();

    QMessageBox msgBox3;
    msgBox3.setText("Go push the button on your bridge you have 30 seconds hurry!.");
    msgBox3.exec();

    hue::Bridge B = connectToBridge();//make new connection.

    //sets all nessasary to disk
    QVariant QBridgeIP = QString::fromStdString(B.getBridgeIP());
    connectionVal.setValue("bridgeIP", QBridgeIP);
    int port = B.getBridgePort();
    connectionVal.setValue("bridgePort", port);
    QVariant QBridgeUsername = QString::fromStdString(B.getUsername());
    connectionVal.setValue("bridgeUsername", QBridgeUsername);

    //get values from connecttionValue and set to varibles to pass into line 59
    port = connectionVal.value("bridgePort").toInt();
    username = connectionVal.value("bridgeUsername").toString();
    ipAddress = connectionVal.value("bridgeIP").toString();

    QMessageBox msgBox2;

    msgBox2.setText("Bridge info:   " + username + "   Bridge ip:   " + ipAddress + "   Port:  " + QString::fromStdString(std::to_string(port)));
    msgBox2.exec();
    }
}

