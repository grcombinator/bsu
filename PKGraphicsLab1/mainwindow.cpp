#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QColor>
#include <algorithm>
#include <cmath>
#include <QPushButton>
#include <QColorDialog>
#include <QLineEdit>
#include <QDebug>
#include <QIntValidator>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), updating(false) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // RGB
    layout->addWidget(new QLabel("RGB"));
    QHBoxLayout *rLayout = new QHBoxLayout();
    rLayout->addWidget(new QLabel("R:"));
    rSlider = new QSlider(Qt::Horizontal);
    rInput = new QLineEdit(this);
    rLayout->addWidget(rSlider);
    rLayout->addWidget(rInput);
    layout->addLayout(rLayout);
    QIntValidator *validator = new QIntValidator;
    rInput->setValidator(validator);

    QHBoxLayout *gLayout = new QHBoxLayout();
    gLayout->addWidget(new QLabel("G:"));
    gSlider = new QSlider(Qt::Horizontal);
    gInput = new QLineEdit(this);
    gLayout->addWidget(gSlider);
    gLayout->addWidget(gInput);
    layout->addLayout(gLayout);
    gInput->setValidator(validator);

    QHBoxLayout *bLayout = new QHBoxLayout();
    bLayout->addWidget(new QLabel("B:"));
    bSlider = new QSlider(Qt::Horizontal);
    bInput = new QLineEdit(this);
    bLayout->addWidget(bSlider);
    bLayout->addWidget(bInput);
    layout->addLayout(bLayout);
    bInput->setValidator(validator);

// Color Display
    colorDisplay = new QLabel("Current Color");
    colorDisplay->setFixedHeight(50);
    layout->addWidget(colorDisplay);

    // CMYK
    layout->addWidget(new QLabel("CMYK"));
    QHBoxLayout *cLayout = new QHBoxLayout();
    cLayout->addWidget(new QLabel("C:"));
    cSlider = new QSlider(Qt::Horizontal);
    cInput = new QLineEdit(this);
    cLayout->addWidget(cSlider);
    cLayout->addWidget(cInput);
    layout->addLayout(cLayout);
    cInput->setValidator(validator);

    QHBoxLayout *mLayout = new QHBoxLayout();
    mLayout->addWidget(new QLabel("M:"));
    mSlider = new QSlider(Qt::Horizontal);
    mInput = new QLineEdit(this);
    mLayout->addWidget(mSlider);
    mLayout->addWidget(mInput);
    layout->addLayout(mLayout);
    mInput->setValidator(validator);

    QHBoxLayout *yLayout = new QHBoxLayout();
    yLayout->addWidget(new QLabel("Y:"));
    ySlider = new QSlider(Qt::Horizontal);
    yInput = new QLineEdit(this);
    yLayout->addWidget(ySlider);
    yLayout->addWidget(yInput);
    layout->addLayout(yLayout);
    yInput->setValidator(validator);

    QHBoxLayout *kLayout = new QHBoxLayout();
    kLayout->addWidget(new QLabel("K:"));
    kSlider = new QSlider(Qt::Horizontal);
    kInput = new QLineEdit(this);
    kLayout->addWidget(kSlider);
    kLayout->addWidget(kInput);
    layout->addLayout(kLayout);
    kInput->setValidator(validator);

    colorDisplay2 = new QLabel("Current Color");
    colorDisplay2->setFixedHeight(50);
    layout->addWidget(colorDisplay2);

// LAB
    layout->addWidget(new QLabel("LAB"));
    QHBoxLayout *lLayout = new QHBoxLayout();
    lLayout->addWidget(new QLabel("L:"));
    lSlider = new QSlider(Qt::Horizontal);
    lInput = new QLineEdit(this);
    lLayout->addWidget(lSlider);
    lLayout->addWidget(lInput);
    layout->addLayout(lLayout);
    lInput->setValidator(validator);

    QHBoxLayout *aLayout = new QHBoxLayout();
    aLayout->addWidget(new QLabel("A:"));
    aSlider = new QSlider(Qt::Horizontal);
    aInput = new QLineEdit(this);
    aLayout->addWidget(aSlider);
    aLayout->addWidget(aInput);
    layout->addLayout(aLayout);
    aInput->setValidator(validator);

    QHBoxLayout *bLabLayout = new QHBoxLayout();
    bLabLayout->addWidget(new QLabel("B:"));
    bLabSlider = new QSlider(Qt::Horizontal);
    bLabInput = new QLineEdit(this);
    bLabLayout->addWidget(bLabSlider);
    bLabLayout->addWidget(bLabInput);
    layout->addLayout(bLabLayout);
    bLabInput->setValidator(validator);



    //Sliders
    rSlider->setRange(0, 255);
    gSlider->setRange(0, 255);
    bSlider->setRange(0, 255);
    rSlider->setValue(255);
    gSlider->setValue(0);
    bSlider->setValue(0); 

    cSlider->setRange(0, 100);
    mSlider->setRange(0, 100);
    ySlider->setRange(0, 100);
    kSlider->setRange(0, 100);

    lSlider->setRange(0, 100);
    aSlider->setRange(-128, 127);
    bLabSlider->setRange(-128, 127);

    connect(rSlider, &QSlider::valueChanged, this, &MainWindow::updateColorRGB);
    connect(gSlider, &QSlider::valueChanged, this, &MainWindow::updateColorRGB);
    connect(bSlider, &QSlider::valueChanged, this, &MainWindow::updateColorRGB);

    connect(cSlider, &QSlider::valueChanged, this, &MainWindow::updateColorCMYK);
    connect(mSlider, &QSlider::valueChanged, this, &MainWindow::updateColorCMYK);
    connect(ySlider, &QSlider::valueChanged, this, &MainWindow::updateColorCMYK);
    connect(kSlider, &QSlider::valueChanged, this, &MainWindow::updateColorCMYK);

    connect(lSlider, &QSlider::valueChanged, this, &MainWindow::updateColorLAB);
    connect(aSlider, &QSlider::valueChanged, this, &MainWindow::updateColorLAB);
    connect(bLabSlider, &QSlider::valueChanged, this, &MainWindow::updateColorLAB);

    QPushButton *colorPickerButton = new QPushButton("Выбрать цвет", this);
    layout->addWidget(colorPickerButton);
    connect(colorPickerButton, &QPushButton::clicked, this, &MainWindow::openColorPicker);

    // Поля ввода
    rLayout->addWidget(rSlider);
    layout->addLayout(rLayout);

    gLayout->addWidget(gSlider);
    layout->addLayout(gLayout);

    bLayout->addWidget(bSlider);
    layout->addLayout(bLayout);

    cLayout->addWidget(cSlider);
    layout->addLayout(cLayout);

    mLayout->addWidget(mSlider);
    layout->addLayout(mLayout);

    yLayout->addWidget(ySlider);
    layout->addLayout(yLayout);

    kLayout->addWidget(kSlider);
    layout->addLayout(kLayout);

    lLayout->addWidget(lSlider);
    layout->addLayout(lLayout);

    aLayout->addWidget(aSlider);
    layout->addLayout(aLayout);

    bLabLayout->addWidget(bLabSlider);
    layout->addLayout(bLabLayout);

    connect(rInput, &QLineEdit::textChanged, this, [this]() {
        bool ok;
        int value = rInput->text().toInt(&ok);
        if (ok) {
            rSlider->setValue(std::clamp(value, 0, 255));
            updateColorRGB();
        }
    });
    connect(gInput, &QLineEdit::textChanged, this, [this]() {
        bool ok;
        int value = gInput->text().toInt(&ok);
        if (ok) {
            gSlider->setValue(std::clamp(value, 0, 255));
            updateColorRGB();
        }
    });
    connect(bInput, &QLineEdit::textChanged, this, [this]() {
        bool ok;
        int value = bInput->text().toInt(&ok);
        if (ok) {
            bSlider->setValue(std::clamp(value, 0, 255));
            updateColorRGB();
        }
    });
    connect(cInput, &QLineEdit::textChanged, this, [this]() {
        bool ok;
        double value = cInput->text().toDouble(&ok);
        if (ok) {
            cSlider->setValue(std::clamp(static_cast<int>(value), 0, 100));
            updateColorCMYK();
        }
    });
    connect(mInput, &QLineEdit::textChanged, this, [this]() {
        bool ok;
        double value = mInput->text().toDouble(&ok);
        if (ok) {
            mSlider->setValue(std::clamp(static_cast<int>(value), 0, 100));
            updateColorCMYK();
        }
    });
    connect(yInput, &QLineEdit::textChanged, this, [this]() {
        bool ok;
        double value = yInput->text().toDouble(&ok);
        if (ok) {
            ySlider->setValue(std::clamp(static_cast<int>(value), 0, 100));
            updateColorCMYK();
        }
    });
    connect(kInput, &QLineEdit::textChanged, this, [this]() {
        bool ok;
        double value = kInput->text().toDouble(&ok);
        if (ok) {
            kSlider->setValue(std::clamp(static_cast<int>(value), 0, 100));
            updateColorCMYK();
        }
    });
    connect(lInput, &QLineEdit::textChanged, this, [this]() {
        bool ok;
        double value = lInput->text().toDouble(&ok);
        if (ok) {
            lSlider->setValue(std::clamp(static_cast<int>(value), 0, 100));
            updateColorLAB();
        }
    });
    connect(aInput, &QLineEdit::textChanged, this, [this]() {
        bool ok;
        double value = aInput->text().toDouble(&ok);
        if (ok) {
            aSlider->setValue(std::clamp(static_cast<int>(value), -128, 127));
            updateColorLAB();
        }
    });
    connect(bLabInput, &QLineEdit::textChanged, this, [this]() {
        bool ok;
        double value = bLabInput->text().toDouble(&ok);
        if (ok) {
            bLabSlider->setValue(std::clamp(static_cast<int>(value), -128, 127));
            updateColorLAB();
        }
    });

    updateColorRGB();
}

void MainWindow::updateColorRGB() {
    if (updating) return;
    updating = true;
    int r = rSlider->value();
    int g = gSlider->value();
    int b = bSlider->value();

    // Устанавливаем цвет в QLabel
    QColor color(r, g, b);
    colorDisplay->setStyleSheet(QString("background-color: %1").arg(color.name()));
    colorDisplay2->setStyleSheet(QString("background-color: %1").arg(color.name()));

    rInput->setText(QString::number(r));
    gInput->setText(QString::number(g));
    bInput->setText(QString::number(b));

    updateCMYK();
    updateLAB();
    updating = false;
}
void MainWindow::updateColorCMYK() {
    if (updating) return;
    updating = true;
    double c = cSlider->value() / 100.0 ;
    double m = mSlider->value() / 100.0 ;
    double y = ySlider->value() / 100.0 ;
    double k = kSlider->value() / 100.0 ;

    // Преобразование CMYK в RGB
    int r = static_cast<int>(255 * (1 - c) * (1 - k));
    int g = static_cast<int>(255 * (1 - m) * (1 - k));
    int b = static_cast<int>(255 * (1 - y) * (1 - k));

    rSlider->setValue(r);
    gSlider->setValue(g);
    bSlider->setValue(b);

    QColor color(r, g, b);
    colorDisplay->setStyleSheet(QString("background-color: %1").arg(color.name()));
    colorDisplay2->setStyleSheet(QString("background-color: %1").arg(color.name()));


    c*=100;
    m*=100;
    y*=100;
    k*=100;

    cInput->setText(QString::number(c));
    mInput->setText(QString::number(m));
    yInput->setText(QString::number(y));
    kInput->setText(QString::number(k));

    updateLAB();
    updating = false;
}

void MainWindow::updateColorLAB() {
    if (updating) return;
    updating = true;

    double L = lSlider->value();
    double A = aSlider->value();
    double B = bLabSlider->value();

    // Преобразование LAB в XYZ
    double y = (L + 16) / 116;
    double x = A / 500 + y;
    double z = y - B / 200;

    x = 0.95047 * (x * x * x > 0.008856 ? x * x * x : (x - 16 / 116) / 7.787);
    y = 1.00000 * (y * y * y > 0.008856 ? y * y * y : (y - 16 / 116) / 7.787);
    z = 1.08883 * (z * z * z > 0.008856 ? z * z * z : (z - 16 / 116) / 7.787);

    // Преобразование XYZ в RGB
    double r = x * 3.2406 + y * -1.5372 + z * -0.4986;
    double g = x * -0.9689 + y * 1.8758 + z * 0.0415;
    double b = x * 0.0557 + y * -0.2040 + z * 1.0570;


    r = r > 1 ? 1 : (r < 0 ? 0 : r);
    g = g > 1 ? 1 : (g < 0 ? 0 : g);
    b = b > 1 ? 1 : (b < 0 ? 0 : b);

    r = r * 255;
    g = g * 255;
    b = b * 255;

    // Устанавливаем значения RGB в слайдеры
    rSlider->setValue(static_cast<int>(r));
    gSlider->setValue(static_cast<int>(g));
    bSlider->setValue(static_cast<int>(b));

    // Обновляем цвет в QLabel
    QColor color(static_cast<int>(r), static_cast<int>(g), static_cast<int>(b));
    colorDisplay->setStyleSheet(QString("background-color: %1").arg(color.name()));
    colorDisplay2->setStyleSheet(QString("background-color: %1").arg(color.name()));



    lInput->setText(QString::number(L));
    aInput->setText(QString::number(A));
    bLabInput->setText(QString::number(B));

    updateCMYK();
    updating = false;
}

void MainWindow::updateCMYK() {
    int r = rSlider->value();
    int g = gSlider->value();
    int b = bSlider->value();

    // Преобразование RGB в CMYK
    double rNorm = r / 255.0;
    double gNorm = g / 255.0;
    double bNorm = b / 255.0;

    double k = 1 - std::max({rNorm, gNorm, bNorm});
    double c = (1 - rNorm - k) / (1 - k) * 100;
    double m = (1 - gNorm - k) / (1 - k) * 100;
    double y = (1 - bNorm - k) / (1 - k) * 100;

    QString cStr = QString::number(c, 'f', 2);
    QString mStr = QString::number(m, 'f', 2);
    QString yStr = QString::number(y, 'f', 2);
    QString kStr = QString::number(k*100, 'f', 2);

    cSlider->setValue(c);
    mSlider->setValue(m);
    ySlider->setValue(y);
    kSlider->setValue(k);

    cInput->setText(cStr);
    mInput->setText(mStr);
    yInput->setText(yStr);
    kInput->setText(kStr);
}
void MainWindow::updateLAB() {
    int r = rSlider->value();
    int g = gSlider->value();
    int b = bSlider->value();

    // Преобразование RGB в XYZ
    double rNorm = (r / 255.0) > 0.04045 ? pow((r / 255.0 + 0.055) / 1.055, 2.4) : (r / 255.0) / 12.92;
    double gNorm = (g / 255.0) > 0.04045 ? pow((g / 255.0 + 0.055) / 1.055, 2.4) : (g / 255.0) / 12.92;
    double bNorm = (b / 255.0) > 0.04045 ? pow((b / 255.0 + 0.055) / 1.055, 2.4) : (b / 255.0) / 12.92;

    rNorm *= 100;
    gNorm *= 100;
    bNorm *= 100;

    // Преобразование XYZ в LAB
    double x = rNorm * 0.4124564 + gNorm * 0.3575761 + bNorm * 0.1804375;
    double y = rNorm * 0.2126729 + gNorm * 0.7151522 + bNorm * 0.0721750;
    double z = rNorm * 0.0193339 + gNorm * 0.1191920 + bNorm * 0.9503041;

    // Нормировка к D65
    x /= 95.047;
    y /= 100.000;
    z /= 108.883;

    // Преобразование
    double L, a, bLab;

    if (y > 0.008856) {
        L = 116 * pow(y, 1.0 / 3.0) - 16;
    } else {
        L = 903.3 * y;
    }

    a = 500 * (pow(x, 1.0 / 3.0) - pow(y, 1.0 / 3.0));
    bLab = 200 * (pow(y, 1.0 / 3.0) - pow(z, 1.0 / 3.0));

    lSlider->setValue(static_cast<int>(std::clamp(L, 0.0, 100.0)));
    aSlider->setValue(static_cast<int>(std::clamp(a, -128.0, 127.0)));
    bLabSlider->setValue(static_cast<int>(std::clamp(bLab, -128.0, 127.0)));

    lInput->setText(QString::number(lSlider->value()));
    aInput->setText(QString::number(aSlider->value()));
    bLabInput->setText(QString::number(bSlider->value()));
}
void MainWindow::updateRGB() {
    double L = lSlider->value();
    double A = aSlider->value();
    double B = bLabSlider->value();

    // Преобразование LAB в XYZ
    double y = (L > 0.008856) ? (pow((L + 16) / 116, 3)) : (L / 903.3);
    double x = (A / 500.0) + (y);
    double z = y - (B / 200.0);

    x = 95.047 * ((pow(x, 3) > 0.008856) ? pow(x, 3) : (x - 16 / 116) / 7.787);
    y = 100.000 * ((pow(y, 3) > 0.008856) ? pow(y, 3) : (y - 16 / 116) / 7.787);
    z = 108.883 * ((pow(z, 3) > 0.008856) ? pow(z, 3) : (z - 16 / 116) / 7.787);

    // Преобразование XYZ в RGB
    double r = x * 3.2406 + y * -1.5372 + z * -0.4986;
    double g = x * -0.9689 + y * 1.8758 + z * 0.0415;
    double b = x * 0.0557 + y * -0.2040 + z * 1.0570;

    r = std::clamp(r, 0.0, 1.0);
    g = std::clamp(g, 0.0, 1.0);
    b = std::clamp(b, 0.0, 1.0);


    rSlider->setValue(static_cast<int>(r * 255));
    gSlider->setValue(static_cast<int>(g * 255));
    bSlider->setValue(static_cast<int>(b * 255));

    // Обновляем цвет в QLabel
    QColor color(static_cast<int>(r * 255), static_cast<int>(g * 255), static_cast<int>(b * 255));
    colorDisplay->setStyleSheet(QString("background-color: %1").arg(color.name()));
    colorDisplay2->setStyleSheet(QString("background-color: %1").arg(color.name()));


    updateCMYK();
}

void MainWindow::openColorPicker() {
    QColor color = QColorDialog::getColor(QColor(rSlider->value(), gSlider->value(), bSlider->value()), this, "Выберите цвет");

    if (color.isValid()) {
        rSlider->setValue(color.red());
        gSlider->setValue(color.green());
        bSlider->setValue(color.blue());

        updateColorRGB();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
