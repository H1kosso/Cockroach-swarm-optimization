#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Q3DSurface>
#include <QLayout>
#include <QMainWindow>
#include <QVBoxLayout>
#include "testfunctions.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setDefaultRadioButton();
    void setDefaultParametersSchwefel();
    void setDefaultParametersHiper();
    void setDefaultParametersRastring();
    void calculateResult();
    void putGraph(std::vector<double> &allOptimums);
    void removeGraphs(QLayout *layout);
    void functionGraph();
        Ui::MainWindow *ui;

private slots:
    void on_schwefelButton_toggled();

    void on_rastringButton_clicked();

    void on_hiperButton_clicked();

    void on_pushButton_clicked();

private:

};
#endif  // MAINWINDOW_H
