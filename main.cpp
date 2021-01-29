#include <QApplication>
#include <QFormLayout>
#include <QtGlobal>
#include <QObject>
#include <QSlider>
#include <QSpinBox>
#include <QPushButton>
#include <QWidget>
#include <iostream>
#include <memory>

#include "settings.h"
#include "ThreadManager.h"
#include "rtc_base/thread.h"

using namespace vic::rtc;
using namespace std;

int main(int argc, char *argv[]) {
    auto thread = ::rtc::ThreadManager::Instance()->WrapCurrentThread();
    ThreadManager::instance()->init();

    std::cout << "-----current thread: " << thread->name() << std::endl;
    thread->PostTask(RTC_FROM_HERE, [](){
        std::cout << "-----current thread is from post!!!!!!" << endl;
    });

    QApplication app(argc, argv);

    auto window = new QWidget;

    auto spinBox = new QSpinBox;
    spinBox->setRange(0, 100);
    auto slider = new QSlider;
    slider->setRange(0, 100);
    QObject::connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), slider,
                     &QSlider::setValue);
    QObject::connect(slider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);

    auto setting = new settings(window);

    ::rtc::ThreadManager::Instance()->CurrentThread()->PostTask(RTC_FROM_HERE, [](){
        std::cout << "------->Post Task-----> Current Thread: "
                  << ::rtc::ThreadManager::Instance()->CurrentThread()->name() << std::endl;
    });
    ThreadManager::instance()->thread(ThreadName::SERVICE)->PostTask(RTC_FROM_HERE, [setting]() {
        std::cout << "------->Post Task 0-----> Current Thread: "
                  << ::rtc::ThreadManager::Instance()->CurrentThread()->name() << std::endl;
        setting->onCallback();
    });

    auto button = new QPushButton;
    button->setText("Settings");
    QObject::connect(button, &QPushButton::released, setting, &QWidget::show);

    auto layout = new QFormLayout;
    layout->addRow("spin box:", spinBox);
    layout->addRow("slider:", slider);
    layout->addRow("button", button);
    window->setLayout(layout);
//    window->show();

    return app.exec();
}
