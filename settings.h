//
// Created by Vic Ren on 2021/1/14.
//

#ifndef WEBRTC_CPP_DEMO_SETTINGS_H
#define WEBRTC_CPP_DEMO_SETTINGS_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class settings; }
QT_END_NAMESPACE

class settings : public QDialog {
Q_OBJECT

public:
    explicit settings(QWidget *parent = nullptr);

    ~settings() override;

private:
    Ui::settings *ui;
};

#endif //WEBRTC_CPP_DEMO_SETTINGS_H
