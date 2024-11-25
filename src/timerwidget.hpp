#pragma once

#include "ui_timerwidget.h"
#include <QTimer>
#include <QSoundEffect>

#include "tomatotimer.hpp"
#include "tasktablemodel.hpp"

class TimerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimerWidget(QWidget* parent = nullptr);

    void setTimer(TomatoTimer* timer);
    void setModel(TaskTableModel * taskdb);
    
private slots:
    void updateDisplay();
    void start();
    void stop();
    void toggle(bool);
    void intervalTimedOut();
    void completedCurrentTask(bool);

public slots:
    void timerUpdated();

private:
    void updateText();

    Ui::TimerWidget ui;
    QTimer m_timer;
    TomatoTimer* m_tomatotimer = nullptr;
    TaskTableModel* m_taskmodel = nullptr;
    QSoundEffect m_ring;
    bool m_isRunning = false;
    QSortFilterProxyModel m_filterModel;
};