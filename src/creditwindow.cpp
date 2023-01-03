#include "creditwindow.h"
#include "ui_creditwindow.h"

creditwindow::creditwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creditwindow)
{
    ui->setupUi(this);
}

creditwindow::~creditwindow()
{
    delete ui;
}

void creditwindow::on_pushButton_calculate_clicked()
{
    double amount = ui->lineEdit_credit->text().toDouble();
    double percent = ui->spinBox_percent->text().toDouble();
    double months = ui->spinBox_duration->text().toDouble();
    double interest_rate = (percent / (100 * 12));

    double m;
    if (ui->comboBox->currentIndex() == 0) {
        m = amount * (interest_rate / (1 - pow(1 + interest_rate, (-1) * months)));
        ui->label_first->setNum(m);
        ui->label_last->setNum(m);
        ui->label_over->setNum(m * months - amount);
        ui->label_total->setNum(amount + (m * months - amount));
    } else {
        ui->tableWidget->setColumnCount(4);
        ui->tableWidget->setRowCount(months);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Sum" << "Main Credit" << "Percent" << "Loan balance");
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
        QTableWidgetItem *itm;
        double slice = amount / months;
        double sum = 0;

        for (int i = 0; i < (int)months; i++) {
            m = amount * interest_rate;
            amount -= slice;
            sum += m;
            itm = new QTableWidgetItem(QString::number(slice + m,'l',2));
            ui->tableWidget->setItem(i,0,itm);
            itm = new QTableWidgetItem(QString::number(slice,'l',2));
            ui->tableWidget->setItem(i,1,itm);
            itm = new QTableWidgetItem(QString::number(m,'l',2));
            ui->tableWidget->setItem(i,2,itm);
            itm = new QTableWidgetItem(QString::number(amount,'l',2));
            ui->tableWidget->setItem(i,3,itm);

        }
        ui->label_first->setNum(ui->lineEdit_credit->text().toDouble() * interest_rate + slice);
        ui->label_last->setNum(interest_rate * slice + slice);
        ui->label_over->setNum(sum);
        ui->label_total->setNum(ui->lineEdit_credit->text().toDouble() + sum);

    }
}

