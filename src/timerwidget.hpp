#pragma once

#include "ui_timerwidget.h"
#include <QTimer>

#include "tomatotimer.hpp"

class TimerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimerWidget(QWidget* parent = nullptr);


private slots:
    void updateDisplay();
    void start();
    void stop();
    void toggle(bool checked);
    void intervalTimedOut();
private:
    Ui::TimerWidget ui;
    QTimer m_timer;
    TomatoTimer m_tomatotimer;
    bool m_isRunning = false;
};