/**
    \file mainwindow.h
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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include <hueplusplus/BaseDevice.h>
#include <hueplusplus/BaseHttpHandler.h>
#include <hueplusplus/Bridge.h>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_horizontalSlider_rangeChanged(int min, int max);

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_sliderReleased();

    void on_listWidget_itemPressed(QListWidgetItem *item);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_listWidget_itemSelectionChanged();

    void on_listWidget_itemActivated(QListWidgetItem *item);

    void on_horizontalSlider_2_sliderReleased();

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_actionRefresh_lights_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
