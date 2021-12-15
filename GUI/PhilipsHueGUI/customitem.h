#ifndef CUSTOMITEM_H
#define CUSTOMITEM_H

#include <QWidget>

namespace Ui {
class CustomItem;
}

class CustomItem : public QWidget
{
    Q_OBJECT

public:
    explicit CustomItem(QWidget *parent = nullptr);
    ~CustomItem();

    void setText(const QString &text);//set label on costom item
    QString getText();//get text on label

private:
    Ui::CustomItem *ui;
};

#endif // CUSTOMITEM_H
