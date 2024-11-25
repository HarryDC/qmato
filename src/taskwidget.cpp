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
    m_completedModel.setFilterKeyColumn(Task::tableColumn);
    m_currentModel.setFilterFixedString(Task::currentName);
    m_currentModel.setFilterKeyColumn(Task::tableColumn);

    ui.currentView->setModel(&m_currentModel);

    ui.completedView->setModel(&m_completedModel);
}

void TaskWidget::setModel(TaskTableModel* model) {
    m_model = model;
    m_completedModel.setSourceModel(model);
    m_currentModel.setSourceModel(model);
}
