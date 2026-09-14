#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QFileDialog>
#include <QImage>
#include <QFileInfo>
#include <QHeaderView>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class ImageInfoExtractor : public QWidget
{
    Q_OBJECT

public:
    ImageInfoExtractor(QWidget *parent = nullptr);

private slots:
    void chooseDirectory();
    void loadImages(const QString &directory);

private:
    QTableWidget *table;
};
#endif // MAINWINDOW_H
