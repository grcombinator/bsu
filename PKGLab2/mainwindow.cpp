#include "mainwindow.h"
//#include <tiffio.h>
ImageInfoExtractor::ImageInfoExtractor(QWidget *parent)
    : QWidget(parent), table(new QTableWidget(this)) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    QPushButton *button = new QPushButton("Выбрать папку", this);

    layout->addWidget(button);
    layout->addWidget(table);

    connect(button, &QPushButton::clicked, this, &ImageInfoExtractor::chooseDirectory);

    table->setColumnCount(5);
    table->setHorizontalHeaderLabels(QStringList() << "Имя файла" << "Размер (пиксели)" << "Разрешение (dpi)" << "Глубина цвета" << "Сжатие");
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void ImageInfoExtractor::chooseDirectory() {
    QString dir = QFileDialog::getExistingDirectory(this, "Выбрать папку");
    if (!dir.isEmpty()) {
        loadImages(dir);
    }
}

void ImageInfoExtractor::loadImages(const QString &directory) {
    QDir dir(directory);
    QStringList filters = { "*.jpg", "*.jpeg", "*.gif", "*.png", "*.bmp", "*.tif", "*.tiff", "*.pcx" };
    QStringList files = dir.entryList(filters, QDir::Files);

    table->setRowCount(files.size());

    for (int i = 0; i < files.size(); ++i) {
        QImage image(dir.filePath(files[i]));
        QFileInfo fileInfo(dir.filePath(files[i]));

        QString compression;
        if (fileInfo.suffix().toLower() == "jpg" || fileInfo.suffix().toLower() == "jpeg") {
            compression = "Сжатие с потерями (JPEG)";
        } else if (fileInfo.suffix().toLower() == "png") {
            compression = "Без потерь (PNG)";
        } else if (fileInfo.suffix().toLower() == "gif") {
            compression = "Без потерь (GIF)";
        } else if (fileInfo.suffix().toLower() == "bmp") {
            compression = "Без сжатия (BMP)";
        } else if (fileInfo.suffix().toLower() == "tif" || fileInfo.suffix().toLower() == "tiff") {
            compression = "Может быть сжат (TIFF)";
        } else if (fileInfo.suffix().toLower() == "pcx") {
            compression = "Без потерь (PCX)";
        }

        if (!image.isNull()) {
            // Получаем необходимые данные
            QString size = QString("%1 x %2").arg(image.width()).arg(image.height());
            QString dpi = QString("%1 x %2").arg(image.dotsPerMeterX() / 100.0).arg(image.dotsPerMeterY() / 100.0);
            QString colorDepth = QString("%1 бит").arg(image.depth());
            //QString compression = "N/A"; // Для примера, сжатие не реализовано

            table->setItem(i, 0, new QTableWidgetItem(fileInfo.fileName()));
            table->setItem(i, 1, new QTableWidgetItem(size));
            table->setItem(i, 2, new QTableWidgetItem(dpi));
            table->setItem(i, 3, new QTableWidgetItem(colorDepth));
            table->setItem(i, 4, new QTableWidgetItem(compression));
        }
    }
}
