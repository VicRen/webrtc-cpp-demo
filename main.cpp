#include <QApplication>
#include <QFormLayout>
#include <QtGlobal>
#include <QObject>
#include <QSlider>
#include <QSpinBox>
#include <QPushButton>
#include <QWidget>
#include "settings.h"

int main(int argc, char *argv []) {
    QApplication app(argc, argv);

    auto window = new QWidget;

    auto spinBox = new QSpinBox;
    spinBox->setRange(0, 100);
    auto slider = new QSlider;
    slider->setRange(0, 100);
    QObject::connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), slider, &QSlider::setValue);
    QObject::connect(slider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);

    auto setting = new settings(window);

    auto button = new QPushButton;
    button->setText("Settings");
    QObject::connect(button, &QPushButton::released, setting, &QWidget::show);

    auto layout = new QFormLayout;
    layout->addRow("spin box:", spinBox);
    layout->addRow("slider:", slider);
    layout->addRow("button", button);
    window->setLayout(layout);
    window->show();

    return app.exec();
}
