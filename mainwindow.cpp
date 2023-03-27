#include "mainwindow.h"

#include <string>

#include "csoalgorithm.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setDefaultRadioButton() { ui->schwefelButton->setChecked(true); }

void MainWindow::setDefaultParametersSchwefel() {
    ui->cockroachNumberET->setPlainText("500");
    ui->maxIterationsET->setPlainText("200");
    ui->lbET->setPlainText("-500");
    ui->ubET->setPlainText("500");
    ui->stepET->setPlainText("0.1");
    ui->visibilityET->setPlainText("0.1");
    ui->dimET->setPlainText("2");
}
void MainWindow::setDefaultParametersRastring() {
    ui->cockroachNumberET->setPlainText("300");
    ui->maxIterationsET->setPlainText("200");
    ui->lbET->setPlainText("-5.12");
    ui->ubET->setPlainText("5.12");
    ui->stepET->setPlainText("0.1");
    ui->visibilityET->setPlainText("0.1");
    ui->dimET->setPlainText("2");
}
void MainWindow::setDefaultParametersHiper() {
    ui->cockroachNumberET->setPlainText("280");
    ui->maxIterationsET->setPlainText("200");
    ui->lbET->setPlainText("-5.12");
    ui->ubET->setPlainText("5.12");
    ui->stepET->setPlainText("0.1");
    ui->visibilityET->setPlainText("0.1");
    ui->dimET->setPlainText("2");
}

void MainWindow::on_schwefelButton_toggled(bool checked) { setDefaultParametersSchwefel(); }

void MainWindow::on_rastringButton_clicked() { MainWindow::setDefaultParametersRastring(); }

void MainWindow::on_hiperButton_clicked() { MainWindow::setDefaultParametersHiper(); }

void MainWindow::calculateResult() {
    int    numberOfCockroaches = ui->cockroachNumberET->toPlainText().toInt();
    int    maxIterations       = ui->maxIterationsET->toPlainText().toInt();
    double eps                 = 0.001;
    double visual              = ui->visibilityET->toPlainText().toDouble();
    int    dim                 = ui->dimET->toPlainText().toInt();
    double W                   = 0.1;
    double lowerBound          = ui->lbET->toPlainText().toDouble();
    double upperBound          = ui->ubET->toPlainText().toDouble();

    double (*testFunction)(std::vector<double>&, int);

    if (ui->schwefelButton->isChecked())
        testFunction = &Schwefel;
    else if (ui->rastringButton->isChecked())
        testFunction = &Rastring;
    else
        testFunction = &HiperElipsoide;

    CSOAlgorithm algorytm(numberOfCockroaches, dim, maxIterations, lowerBound, upperBound, visual,
                          eps, W, testFunction);
    std::vector<double> solution = algorytm.calculateGlobalOptimum();

    ui->ffxLABEL->setText(QString::number(testFunction(solution, dim)));
    ui->xLABEL->setText(QString::number(solution[0]));
    ui->yLABEL->setText(QString::number(solution[1]));
}

void MainWindow::on_pushButton_clicked() { MainWindow::calculateResult(); }
