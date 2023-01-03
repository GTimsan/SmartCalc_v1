#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "calc.h"
#include <string.h>
#include <string>
#include <iostream>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_77, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_88, SIGNAL(clicked()), this, SLOT(digits_numbers()));

    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_numbers()));

    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_func()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_func()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits_func()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_func()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_func()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits_func()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_func()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_func()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_func()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers() {
    QPushButton* button = (QPushButton*)sender();

    QString all_numbers;
    if (ui->label_1->text() == '0') all_numbers = button->text();
    else all_numbers = (ui->label_1->text() + button->text());
    ui->label_1->setText(all_numbers);
}

void MainWindow::digits_func() {
    QPushButton* button = (QPushButton*)sender();

    QString all_numbers;
    if (ui->label_1->text() == '0') all_numbers = button->text() + "(";
    else all_numbers = (ui->label_1->text() + button->text() + "(");
    ui->label_1->setText(all_numbers);
}

void MainWindow::on_pushButton_dot_clicked()
{
    ui->label_1->setText(ui->label_1->text() + '.');
}

void MainWindow::on_pushButton_ac_clicked()
{
    ui->label_1->setText("0");
    ui->label_2->setText("0");
}

void MainWindow::on_pushButton_del_clicked()
{
    QString str = ui->label_1->text();
    if (str != "0") {

        str.chop(1);
        ui->label_1->setText(str);
    }
}

void MainWindow::on_pushButton_eq_clicked()
{
    QString str = ui->label_1->text();
    if (str != "0" && str != "") {
        QByteArray ba = str.toLocal8Bit();
        char *c_str = ba.data();
        double result = ui->lineEdit->text().toDouble();
        int error = smart_calc_v_1(c_str, &result);
        if (error == 0) {
            ui->label_2->setNum(result);
        } else ui->label_2->setNum(error);
    }
}

void MainWindow::on_pushButton_clicked()
{
    grphWindow = new GraphWindow(this);
    grphWindow->show();
}

void MainWindow::on_pushButton_credit_clicked()
{
    crdtWindow = new creditwindow(this);
    crdtWindow->show();

}
