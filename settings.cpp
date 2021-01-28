//
// Created by Vic Ren on 2021/1/14.
//

// You may need to build the project (run Qt uic code generator) to get "ui_settings.h" resolved

#include <iostream>

#include "settings.h"
#include "ui_settings.h"

#include "webrtc/ThreadManager.h"

using namespace vic::rtc;

settings::settings(QWidget *parent) :
        QDialog(parent), ui(new Ui::settings) {
    ui->setupUi(this);
}

settings::~settings() {
    delete ui;
}

void settings::onCallback() {
    std::cout << "------->Post Task 1-----> Current Thread: " << ::rtc::ThreadManager::Instance()->CurrentThread()->name() << std::endl;
    ThreadManager::instance()->thread(ThreadName::MAIN)->PostTask(RTC_FROM_HERE, [wself = weak_from_this()](){
        std::cout << "------->Post Task 2-----> Current Thread: " << ::rtc::ThreadManager::Instance()->CurrentThread()->name() << std::endl;
    });
    ThreadManager::instance()->thread(ThreadName::WORKER)->PostTask(RTC_FROM_HERE, [wself = weak_from_this()](){
        std::cout << "------->Post Task 3-----> Current Thread: " << ::rtc::ThreadManager::Instance()->CurrentThread()->name() << std::endl;
        ThreadManager::instance()->thread(ThreadName::SERVICE)->PostTask(RTC_FROM_HERE, [wself](){
            std::cout << "------->Post Task 4-----> Current Thread: " << ::rtc::ThreadManager::Instance()->CurrentThread()->name() << std::endl;
            ThreadManager::instance()->thread(ThreadName::WORKER)->PostTask(RTC_FROM_HERE, [wself](){
                std::cout << "------->Post Task 5-----> Current Thread: " << ::rtc::ThreadManager::Instance()->CurrentThread()->name() << std::endl;
            });
        });
    });
}
