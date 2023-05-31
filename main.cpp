#include <QApplication>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <iostream>
#include <vector>

#include "csoalgorithm.h"
#include "mainwindow.h"
#include "testfunctions.h"
#include "exprtk.hpp"

int main(int argc, char *argv[]) {
    qputenv("QSG_RHI_BACKEND", "opengl");
    QApplication a(argc, argv);
    MainWindow   w;
    w.show();
    w.setDefaultRadioButton();

    return a.exec();
}
