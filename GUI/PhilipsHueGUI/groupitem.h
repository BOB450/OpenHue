#ifndef GROUPITEM_H
#define GROUPITEM_H

#include <QWidget>

namespace Ui {
class GroupItem;
}

class GroupItem : public QWidget
{
    Q_OBJECT

public:
    explicit GroupItem(QWidget *parent = nullptr);
    ~GroupItem();

    void setText(const QString &text);//set label on costom item
    QString getText();//get text on label

private:
    Ui::GroupItem *ui;
};

#endif // GROUPITEM_H
