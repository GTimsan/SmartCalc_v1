#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDialog>
#include <QtMath>

namespace Ui {
class creditwindow;
}

class creditwindow : public QDialog
{
    Q_OBJECT

public:
    explicit creditwindow(QWidget *parent = nullptr);
    ~creditwindow();

private slots:
    void on_pushButton_calculate_clicked();

private:
    Ui::creditwindow *ui;
};

#endif // CREDITWINDOW_H
