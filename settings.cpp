//
// Created by Vic Ren on 2021/1/14.
//

// You may need to build the project (run Qt uic code generator) to get "ui_settings.h" resolved

#include "settings.h"
#include "ui_settings.h"

settings::settings(QWidget *parent) :
        QDialog(parent), ui(new Ui::settings) {
    ui->setupUi(this);
}

settings::~settings() {
    delete ui;
}
