#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QDialog>
#include <QVector>
#include <QTimer>
#include <QtMath>

extern "C" {
#include "calc.h"
}

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GraphWindow(QWidget *parent = nullptr);
    ~GraphWindow();

private slots:
    void on_pushButton_2_clicked();


private:
    Ui::GraphWindow *ui;

};

#endif // GRAPHWINDOW_H
