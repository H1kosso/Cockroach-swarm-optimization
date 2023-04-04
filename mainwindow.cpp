#include "mainwindow.h"

#include <Q3DScatter>
#include <Q3DSurface>
#include <QApplication>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QScatterSeries>
#include <QSurface3DSeries>
#include <QSurfaceDataArray>
#include <QValueAxis>
#include <QtGui/QPainter>
#include <QtGui/QScreen>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <algorithm>
#include <string>

#include "csoalgorithm.h"
#include "surfacegraph.h"
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
    ui->epsET->setPlainText("0.001");
}
void MainWindow::setDefaultParametersRastring() {
    ui->cockroachNumberET->setPlainText("300");
    ui->maxIterationsET->setPlainText("200");
    ui->lbET->setPlainText("-5.12");
    ui->ubET->setPlainText("5.12");
    ui->stepET->setPlainText("0.1");
    ui->visibilityET->setPlainText("0.1");
    ui->dimET->setPlainText("2");
    ui->epsET->setPlainText("0.001");
}
void MainWindow::setDefaultParametersHiper() {
    ui->cockroachNumberET->setPlainText("280");
    ui->maxIterationsET->setPlainText("200");
    ui->lbET->setPlainText("-5.12");
    ui->ubET->setPlainText("5.12");
    ui->stepET->setPlainText("0.1");
    ui->visibilityET->setPlainText("0.1");
    ui->dimET->setPlainText("2");
    ui->epsET->setPlainText("0.001");
}

void MainWindow::on_schwefelButton_toggled() { setDefaultParametersSchwefel(); }

void MainWindow::on_rastringButton_clicked() { MainWindow::setDefaultParametersRastring(); }

void MainWindow::on_hiperButton_clicked() { MainWindow::setDefaultParametersHiper(); }

void MainWindow::calculateResult() {
    int                 numberOfCockroaches = ui->cockroachNumberET->toPlainText().toInt();
    int                 maxIterations       = ui->maxIterationsET->toPlainText().toInt();
    double              eps                 = ui->epsET->toPlainText().toDouble();
    double              visual              = ui->visibilityET->toPlainText().toDouble();
    int                 dim                 = ui->dimET->toPlainText().toInt();
    double              W                   = 0.1;
    double              lowerBound          = ui->lbET->toPlainText().toDouble();
    double              upperBound          = ui->ubET->toPlainText().toDouble();
    std::vector<double> allOptimums;
    double (*testFunction)(std::vector<double> &, int);

    if (ui->schwefelButton->isChecked())
        testFunction = &Schwefel;
    else if (ui->rastringButton->isChecked())
        testFunction = &Rastring;
    else if (ui->hiperButton->isChecked()) {
        testFunction = &HiperElipsoide;
    } else {
        testFunction = &CustomFunction;
    }

    CSOAlgorithm algorytm(numberOfCockroaches, dim, maxIterations, lowerBound, upperBound, visual,
                          eps, W, testFunction);
    std::vector<double> solution = algorytm.calculateGlobalOptimum(allOptimums);

    ui->ffxLABEL->setText(QString::number(testFunction(solution, dim)));
    ui->xLABEL->setText(QString::number(solution[0]));
    ui->yLABEL->setText(QString::number(solution[1]));
    MainWindow::removeGraphs(ui->graphs);
    putGraph(allOptimums);
    functionGraph();
}

void MainWindow::on_pushButton_clicked() { MainWindow::calculateResult(); }

void MainWindow::putGraph(std::vector<double> &allOptimums) {
    QLineSeries *series = new QLineSeries();

    for (unsigned long long int i = 0; i < allOptimums.size(); i++) {
        series->append(i + 1, allOptimums[i]);
        qInfo() << allOptimums[i] << " " << i;
    }
    double min = *std::min_element(allOptimums.begin(), allOptimums.end()) - 0.005;
    double max = *std::max_element(allOptimums.begin(), allOptimums.end());
    // Tworzenie wykresu i dodanie serii danych
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle("");

    // Ustawienie osi X i Y
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, (int)allOptimums.size());
    axisX->setLabelFormat("%i");
    axisX->setTitleText("Iteracja");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(min, max);
    axisY->setTitleText("Optimum globalne");
    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisY);

    // Tworzenie widoku wykresu i dodanie do kontenera
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->graphs->addWidget(chartView);
}

void MainWindow::removeGraphs(QLayout *layout) {
    QLayoutItem *child;
    while (layout->count() != 0) {
        child = layout->takeAt(0);
        if (child->layout() != 0) {
            removeGraphs(child->layout());
        } else if (child->widget() != 0) {
            delete child->widget();
        }

        delete child;
    }
}

void MainWindow::functionGraph() {
    Q3DSurface *graph     = new Q3DSurface();
    QWidget *   container = QWidget::createWindowContainer(graph);
    //! [0]

    QSize screenSize = graph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    //! [1]
    QWidget *    widget  = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);
    vLayout->setAlignment(Qt::AlignTop);
    //! [1]

    widget->setWindowTitle(QStringLiteral("Wykres funkcji"));

    QGroupBox *modelGroupBox = new QGroupBox(QStringLiteral("Model"));

    QRadioButton *sqrtSinModelRB = new QRadioButton(widget);
    sqrtSinModelRB->setText(QStringLiteral("Funkcja"));
    sqrtSinModelRB->setChecked(false);

    QVBoxLayout *modelVBox = new QVBoxLayout;
    modelVBox->addWidget(sqrtSinModelRB);
    modelGroupBox->setLayout(modelVBox);

    QGroupBox *selectionGroupBox = new QGroupBox(QStringLiteral("Tryb zaznaczania"));

    QRadioButton *modeNoneRB = new QRadioButton(widget);
    modeNoneRB->setText(QStringLiteral("Brak zaznaczenia"));
    modeNoneRB->setChecked(false);

    QRadioButton *modeItemRB = new QRadioButton(widget);
    modeItemRB->setText(QStringLiteral("Punkt"));
    modeItemRB->setChecked(false);

    QRadioButton *modeSliceRowRB = new QRadioButton(widget);
    modeSliceRowRB->setText(QStringLiteral("Wiersz"));
    modeSliceRowRB->setChecked(false);

    QRadioButton *modeSliceColumnRB = new QRadioButton(widget);
    modeSliceColumnRB->setText(QStringLiteral("Kolumna"));
    modeSliceColumnRB->setChecked(false);

    QVBoxLayout *selectionVBox = new QVBoxLayout;
    selectionVBox->addWidget(modeNoneRB);
    selectionVBox->addWidget(modeItemRB);
    selectionVBox->addWidget(modeSliceRowRB);
    selectionVBox->addWidget(modeSliceColumnRB);
    selectionGroupBox->setLayout(selectionVBox);

    QSlider *axisMinSliderX = new QSlider(Qt::Horizontal, widget);
    axisMinSliderX->setMinimum(0);
    axisMinSliderX->setTickInterval(1);
    axisMinSliderX->setEnabled(true);
    QSlider *axisMaxSliderX = new QSlider(Qt::Horizontal, widget);
    axisMaxSliderX->setMinimum(1);
    axisMaxSliderX->setTickInterval(1);
    axisMaxSliderX->setEnabled(true);
    QSlider *axisMinSliderZ = new QSlider(Qt::Horizontal, widget);
    axisMinSliderZ->setMinimum(0);
    axisMinSliderZ->setTickInterval(1);
    axisMinSliderZ->setEnabled(true);
    QSlider *axisMaxSliderZ = new QSlider(Qt::Horizontal, widget);
    axisMaxSliderZ->setMinimum(1);
    axisMaxSliderZ->setTickInterval(1);
    axisMaxSliderZ->setEnabled(true);

    QComboBox *themeList = new QComboBox(widget);
    themeList->addItem(QStringLiteral("Qt"));
    themeList->addItem(QStringLiteral("Primary Colors"));
    themeList->addItem(QStringLiteral("Digia"));
    themeList->addItem(QStringLiteral("Stone Moss"));
    themeList->addItem(QStringLiteral("Army Blue"));
    themeList->addItem(QStringLiteral("Retro"));
    themeList->addItem(QStringLiteral("Ebony"));
    themeList->addItem(QStringLiteral("Isabelle"));

    QGroupBox *colorGroupBox = new QGroupBox(QStringLiteral("Niestandardowy"));

    QLinearGradient grBtoY(0, 0, 1, 100);
    grBtoY.setColorAt(1.0, Qt::black);
    grBtoY.setColorAt(0.67, Qt::blue);
    grBtoY.setColorAt(0.33, Qt::red);
    grBtoY.setColorAt(0.0, Qt::yellow);
    QPixmap  pm(24, 100);
    QPainter pmp(&pm);
    pmp.setBrush(QBrush(grBtoY));
    pmp.setPen(Qt::NoPen);
    pmp.drawRect(0, 0, 24, 100);
    QPushButton *gradientBtoYPB = new QPushButton(widget);
    gradientBtoYPB->setIcon(QIcon(pm));
    gradientBtoYPB->setIconSize(QSize(24, 100));

    QLinearGradient grGtoR(0, 0, 1, 100);
    grGtoR.setColorAt(1.0, Qt::darkGreen);
    grGtoR.setColorAt(0.5, Qt::yellow);
    grGtoR.setColorAt(0.2, Qt::red);
    grGtoR.setColorAt(0.0, Qt::darkRed);
    pmp.setBrush(QBrush(grGtoR));
    pmp.drawRect(0, 0, 24, 100);
    QPushButton *gradientGtoRPB = new QPushButton(widget);
    gradientGtoRPB->setIcon(QIcon(pm));
    gradientGtoRPB->setIconSize(QSize(24, 100));

    QHBoxLayout *colorHBox = new QHBoxLayout;
    colorHBox->addWidget(gradientBtoYPB);
    colorHBox->addWidget(gradientGtoRPB);
    colorGroupBox->setLayout(colorHBox);

    vLayout->addWidget(modelGroupBox);
    vLayout->addWidget(selectionGroupBox);
    vLayout->addWidget(new QLabel(QStringLiteral("Zakres kolumn")));
    vLayout->addWidget(axisMinSliderX);
    vLayout->addWidget(axisMaxSliderX);
    vLayout->addWidget(new QLabel(QStringLiteral("Zakres wierszy")));
    vLayout->addWidget(axisMinSliderZ);
    vLayout->addWidget(axisMaxSliderZ);
    vLayout->addWidget(new QLabel(QStringLiteral("Motyw")));
    vLayout->addWidget(themeList);
    vLayout->addWidget(colorGroupBox);

    widget->show();

    SurfaceGraph *modifier = new SurfaceGraph(graph);

    QObject::connect(sqrtSinModelRB, &QRadioButton::toggled, modifier,
                     &SurfaceGraph::enableSqrtSinModel);
    QObject::connect(modeNoneRB, &QRadioButton::toggled, modifier, &SurfaceGraph::toggleModeNone);
    QObject::connect(modeItemRB, &QRadioButton::toggled, modifier, &SurfaceGraph::toggleModeItem);
    QObject::connect(modeSliceRowRB, &QRadioButton::toggled, modifier,
                     &SurfaceGraph::toggleModeSliceRow);
    QObject::connect(modeSliceColumnRB, &QRadioButton::toggled, modifier,
                     &SurfaceGraph::toggleModeSliceColumn);
    QObject::connect(axisMinSliderX, &QSlider::valueChanged, modifier, &SurfaceGraph::adjustXMin);
    QObject::connect(axisMaxSliderX, &QSlider::valueChanged, modifier, &SurfaceGraph::adjustXMax);
    QObject::connect(axisMinSliderZ, &QSlider::valueChanged, modifier, &SurfaceGraph::adjustZMin);
    QObject::connect(axisMaxSliderZ, &QSlider::valueChanged, modifier, &SurfaceGraph::adjustZMax);
    QObject::connect(themeList, SIGNAL(currentIndexChanged(int)), modifier, SLOT(changeTheme(int)));
    QObject::connect(gradientBtoYPB, &QPushButton::pressed, modifier,
                     &SurfaceGraph::setBlackToYellowGradient);
    QObject::connect(gradientGtoRPB, &QPushButton::pressed, modifier,
                     &SurfaceGraph::setGreenToRedGradient);

    modifier->setAxisMinSliderX(axisMinSliderX);
    modifier->setAxisMaxSliderX(axisMaxSliderX);
    modifier->setAxisMinSliderZ(axisMinSliderZ);
    modifier->setAxisMaxSliderZ(axisMaxSliderZ);

    sqrtSinModelRB->setChecked(true);
    modeItemRB->setChecked(true);
    themeList->setCurrentIndex(2);
}
