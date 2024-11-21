#pragma once

#include "ui_timerwidget.h"
#include <QTimer>
#include <QSoundEffect>

#include "tomatotimer.hpp"
#include "taskdb.hpp"

class TimerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimerWidget(QWidget* parent = nullptr);

    void setTimer(TomatoTimer* timer);
    void setTaskDB(TaskDB* taskdb);

private slots:
    void updateDisplay();
    void start();
    void stop();
    void toggle(bool checked);
    void intervalTimedOut();

public slots:
    void timerUpdated();

private:
    void updateTasks();
    void updateText();

    Ui::TimerWidget ui;
    QTimer m_timer;
    TomatoTimer* m_tomatotimer = nullptr;
    TaskDB* m_taskdb = nullptr;
    QSoundEffect m_ring;
    bool m_isRunning = false;
};