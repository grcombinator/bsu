#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ImageInfoExtractor window;
    window.setWindowTitle("Image Info Extractor");
    window.resize(800, 600);
    window.show();
    return app.exec();
}
