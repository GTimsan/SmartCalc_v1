#include "graphwindow.h"
#include "ui_graphwindow.h"
//#include "mainwindow.h"

GraphWindow::GraphWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::on_pushButton_2_clicked()
{
    QVector<double> x, y;

    double xBegin = ui->doubleSpinBox_xStart->value();
    double xEnd = ui->doubleSpinBox_xEnd->value();
    double h = fabs(xBegin - xEnd) / 100000;
    double yBegin = ui->doubleSpinBox_yStart->value();
    double yEnd = ui->doubleSpinBox_yEnd->value();

    ui->widget->clearGraphs();
    x.clear();
    y.clear();

    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->yAxis->setRange(yBegin, yEnd);
    double y_var;

    QString str = ui->lineEdit_2->text();
    QByteArray ba = str.toLocal8Bit();
    char* c_str = ba.data();

    for (double X = xBegin; X <= xEnd; ) {
        y_var = X;
        smart_calc_v_1(c_str, &y_var);
        if (!isnan(y_var) && y_var >= yBegin && y_var <=yEnd) {
            x.push_back(X);
            y.push_back(y_var);
        }
        X += h;
    }
    ui ->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
}


