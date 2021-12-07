#include "bridgeselect.h"
#include "ui_bridgeselect.h"

BridgeSelect::BridgeSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BridgeSelect)
{
    ui->setupUi(this);
}

BridgeSelect::~BridgeSelect()
{
    delete ui;
}
