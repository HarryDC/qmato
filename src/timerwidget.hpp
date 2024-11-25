// Copyright 2024 Harald Scheirich
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License

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