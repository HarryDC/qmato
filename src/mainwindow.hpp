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

#pragma once

#include "ui_mainwindow.h"

#include <QTimer>
#include <QVariant>

#include "tomatotimer.hpp"
#include "tasktablemodel.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void loadTasks();
    void saveTasks();


private:
    QVariant loadJson(const QString& filename);
    QVariant saveJson(const QJsonDocument& doc, const QString& filename);

    Ui::MainWindow ui;
    TomatoTimer m_tomatoTimer;
    TaskTableModel m_taskModel;
};