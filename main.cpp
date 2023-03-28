#include <QApplication>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <iostream>
#include <vector>

#include "csoalgorithm.h"
#include "mainwindow.h"
#include "testfunctions.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow   w;
    w.show();
    w.setDefaultRadioButton();

    return a.exec();
}
