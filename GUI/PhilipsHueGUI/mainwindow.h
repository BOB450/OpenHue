#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>

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

    void on_pushButton_3_clicked();

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
