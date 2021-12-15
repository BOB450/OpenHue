#include "customitem.h"
#include "ui_customitem.h"

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
