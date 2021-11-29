/**
    \file mainwindow.cpp
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


#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <thread>
#include <QListWidget>
#include <QListWidgetItem>
#include <QColorDialog>
#include <QColor>

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
 std::string macAddress = "";
 std::string username = "";
 std::string ipAddress = "";
 int port;

// pre made connection will not be used for final product
auto handler = std::make_shared<hueplusplus::LinHttpHandler>();//linhttphandler is only for linux
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

//called when the conect ot bridge button is pressed and then it sets hub eqal to connectToBridge()
void MainWindow::on_pushButton_clicked()
{
    hue::Bridge hueB = connectToBridge();
}


void MainWindow::on_pushButton_2_clicked()
{
    lightsTogle(bridge,3);
}

// Adds lights to the list wigit by looping though all the lights and adding each by there name.
void MainWindow::on_pushButton_3_clicked()
{
    std::vector<hue::Light> allLights = getLight(bridge);
    int Lsize =  allLights.size();
 //   QMessageBox msgBox;
   //  QString qlight = QString::fromStdString(allLights[1].getName());
   // msgBox.setText(qlight);
   // msgBox.exec();

    for(int i = 0; i < Lsize; i++)
    {
        QString qlight = QString::fromStdString(allLights[i].getName());

        ui->listWidget->addItem(qlight);
    }

}

// Togles selected light by getting selected list item then looping through all lights and checking
// if the names match if they do then check if light if so then turn on if not then turn off.
void MainWindow::on_pushButton_4_clicked()
{
   QString text = ui->listWidget->currentItem()->text();
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


void MainWindow::on_pushButton_5_clicked() //change color of selected light
{
    QString text = ui->listWidget->currentItem()->text();
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


void MainWindow::on_horizontalSlider_sliderReleased()
{
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
}


void MainWindow::on_listWidget_itemPressed(QListWidgetItem *item)
{

}

//When a light is clicked set the britness of the light eqal to the slider
void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString text = ui->listWidget->currentItem()->text();
     std::vector<hue::Light> allLights = getLight(bridge);
     int Lsize =  allLights.size();
     for(int i = 0; i < Lsize; i++)
     {
         QString qlight = QString::fromStdString(allLights[i].getName());
         if(qlight == text)
         {


            int bri = allLights[i].getBrightness(); // get brightness from light
            ui->horizontalSlider->setValue(bri); // set position of slider to that of the selected light
            int Ctemp = allLights[i].getColorTemperature(); // get color temp from light
            ui->horizontalSlider_2->setValue(Ctemp);
         }
     }
}


void MainWindow::on_listWidget_itemSelectionChanged()
{

}

//When a light is clicked set the britness of the light eqal to the slider
void MainWindow::on_listWidget_itemActivated(QListWidgetItem *item)
{
    QString text = ui->listWidget->currentItem()->text();
     std::vector<hue::Light> allLights = getLight(bridge);
     int Lsize =  allLights.size();
     for(int i = 0; i < Lsize; i++)
     {
         QString qlight = QString::fromStdString(allLights[i].getName());
         if(qlight == text)
         {


            int bri = allLights[i].getBrightness(); // get brightness from light
            ui->horizontalSlider->setValue(bri); // set position of slider to that of the selected light
            int Ctemp = allLights[i].getColorTemperature(); // get color temp from light
            ui->horizontalSlider_2->setValue(Ctemp);
         }
     }
}

//slider for warmth of light
void MainWindow::on_horizontalSlider_2_sliderReleased()
{
    int ipos = ui->horizontalSlider_2->sliderPosition();

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
             if(allLights[i].hasTemperatureControl())
             {
            // int z = allLights[i].getColorTemperature();
             //QString tempt = QString::number(z);
              //QMessageBox msgBox;

              //msgBox.setText(tempt);
              //msgBox.exec();

            allLights[i].setColorTemperature(ipos);
         }
         }
     }
}

// When you change a item using arrow keys or sutch it will now update the sliders.
void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QString text = ui->listWidget->currentItem()->text();
     std::vector<hue::Light> allLights = getLight(bridge);
     int Lsize =  allLights.size();
     for(int i = 0; i < Lsize; i++)
     {
         QString qlight = QString::fromStdString(allLights[i].getName());
         if(qlight == text)
         {


            int bri = allLights[i].getBrightness(); // get brightness from light
            ui->horizontalSlider->setValue(bri); // set position of slider to that of the selected light
            int Ctemp = allLights[i].getColorTemperature(); // get color temp from light
            ui->horizontalSlider_2->setValue(Ctemp);
         }
     }
}

