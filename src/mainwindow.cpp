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
// limitations under the License.

#include "mainwindow.hpp"
#include "task.hpp"

#include <QVector>
#include <format>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    m_tomatoTimer(this)
{
    QVector<Task> tasks;
    ui.setupUi(this);
    {
        Task t = {.id = 1, .name = "Task1", .table = Task::currentName};
        tasks.push_back(t);
    }
    {
        Task t = {.id = 2,  .name = "Task2", .table = Task::currentName };
        tasks.push_back(t);
    }
    {
        Task t = { .id = 3,  .name = "Task2", .table = Task::backlogName};
        tasks.push_back(t);
    }

    m_taskModel.setTasks(tasks);

    ui.timerWidget->setTimer(&m_tomatoTimer);
    ui.timerWidget->setModel(&m_taskModel);
    ui.settingsWidget->setTimer(&m_tomatoTimer);
    ui.tasksWidget->setModel(&m_taskModel);
    connect(ui.settingsWidget, &SettingsWidget::updated, ui.timerWidget, &TimerWidget::timerUpdated);
}
