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

#include "taskwidget.hpp"

TaskWidget::TaskWidget(QWidget* parent) : QWidget(parent) 
{
    ui.setupUi(this);
    m_completedModel.setFilterFixedString(Task::completedName);
    m_completedModel.setFilterKeyColumn(TaskTableModel::tableColumn);
    m_currentModel.setFilterFixedString(Task::currentName);
    m_currentModel.setFilterKeyColumn(TaskTableModel::tableColumn);

    ui.currentView->setModel(&m_currentModel);
    ui.completedView->setModel(&m_completedModel);

    connect(ui.addButton, &QPushButton::clicked, this, &TaskWidget::onAdd);
}

void TaskWidget::setModel(TaskTableModel* model) {
    m_model = model;
    m_completedModel.setSourceModel(model);
    m_currentModel.setSourceModel(model);
    // Can't set this in the constructor as the model is null
    ui.currentView->setModelColumn(TaskTableModel::nameColumn);
    ui.completedView->setModelColumn(TaskTableModel::nameColumn);
}

void TaskWidget::onDelete(bool)
{

}

void TaskWidget::onAdd(bool)
{
    Task t;
    t.name = "New Task";
    t.table = Task::currentName;
    m_model->insertRow(m_model->rowCount(QModelIndex()), t);
}
