#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QLineEdit>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateColorRGB();
    void updateColorCMYK();
    void updateColorLAB();
    void openColorPicker();

private:
    bool updating;

    void updateCMYK();
    void updateRGB();
    void updateLAB();

    QSlider *rSlider;
    QSlider *gSlider;
    QSlider *bSlider;
    QLabel *colorDisplay;
    QLabel *colorDisplay2;


    QSlider *cSlider;
    QSlider *mSlider;
    QSlider *ySlider;
    QSlider *kSlider;

    QSlider *lSlider;
    QSlider *aSlider;
    QSlider *bLabSlider;

    QLineEdit *rInput;
    QLineEdit *gInput;
    QLineEdit *bInput;
    QLineEdit *cInput;
    QLineEdit *mInput;
    QLineEdit *yInput;
    QLineEdit *kInput;
    QLineEdit *lInput;
    QLineEdit *aInput;
    QLineEdit *bLabInput;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
