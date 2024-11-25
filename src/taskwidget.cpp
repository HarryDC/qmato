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
