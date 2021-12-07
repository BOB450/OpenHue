#ifndef BRIDGESELECT_H
#define BRIDGESELECT_H

#include <QWidget>

namespace Ui {
class BridgeSelect;
}

class BridgeSelect : public QWidget
{
    Q_OBJECT

public:
    explicit BridgeSelect(QWidget *parent = nullptr);
    ~BridgeSelect();

private:
    Ui::BridgeSelect *ui;
};

#endif // BRIDGESELECT_H
