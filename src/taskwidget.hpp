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
#include "ui_taskwidget.h"

#include <QWidget>
#include <QSortFilterProxyModel>

#include "tasktablemodel.hpp"

class TaskWidget : public QWidget {
    Q_OBJECT
public:
    TaskWidget(QWidget* parent = nullptr);;

    void setModel(TaskTableModel* model);

public slots:
    void onDelete(bool);
    void onAdd(bool);

private:
    Ui::TaskWidget ui;

    TaskTableModel* m_model = nullptr;

    QSortFilterProxyModel m_completedModel;
    QSortFilterProxyModel m_currentModel;
};