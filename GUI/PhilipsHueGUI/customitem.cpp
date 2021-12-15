#include "customitem.h"
#include "ui_customitem.h"
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

CustomItem::CustomItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomItem)
{
    ui->setupUi(this);
}

CustomItem::~CustomItem()
{
    delete ui;
}
