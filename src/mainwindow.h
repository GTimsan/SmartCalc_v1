#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphwindow.h"
#include "creditwindow.h"

extern "C" {
#include "calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    GraphWindow* grphWindow;
    creditwindow* crdtWindow;

private slots:
    void digits_numbers();
    void digits_func();
    void on_pushButton_dot_clicked();
//    void operations();
    void on_pushButton_ac_clicked();
    void on_pushButton_eq_clicked();
    void on_pushButton_del_clicked();
    void on_pushButton_clicked();
    void on_pushButton_credit_clicked();
};

#endif // MAINWINDOW_H
