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
#include "rtc_base/ssl_adapter.h"
#include "rtc_base/physical_socket_server.h"
#include "StatsReporter.h"
#include "modules/utility/include/process_thread.h"

using namespace vic::rtc;
using namespace std;

class CustomSocketServer : public rtc::PhysicalSocketServer {

};

int main(int argc, char *argv[]) {
    rtc::InitializeSSL();

    auto *socket_server = new CustomSocketServer;
    auto *thread = new rtc::AutoSocketServerThread(socket_server);
    rtc::ThreadManager::Instance()->SetCurrentThread(thread);
    ThreadManager::instance()->init();

    StatsReporter statsReporter;

    auto pThread = webrtc::ProcessThread::Create("StatsReporterThread");
    pThread->RegisterModule(&statsReporter, RTC_FROM_HERE);
    pThread->Start();

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
