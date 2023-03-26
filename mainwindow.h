#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void on_schwefelButton_toggled(bool checked);

    void on_rastringButton_clicked();

    void on_hiperButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
