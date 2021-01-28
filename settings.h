//
// Created by Vic Ren on 2021/1/14.
//

#ifndef WEBRTC_CPP_DEMO_SETTINGS_H
#define WEBRTC_CPP_DEMO_SETTINGS_H

#include <QDialog>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class settings; }
QT_END_NAMESPACE

class settings : public QDialog, public std::enable_shared_from_this<settings> {
Q_OBJECT

public:
    explicit settings(QWidget *parent = nullptr);

    ~settings() override;

public:
    void onCallback();

private:
    Ui::settings *ui;
};

#endif //WEBRTC_CPP_DEMO_SETTINGS_H
