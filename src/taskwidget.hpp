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

private:
    Ui::TaskWidget ui;

    TaskTableModel* m_model = nullptr;

    QSortFilterProxyModel m_completedModel;
    QSortFilterProxyModel m_currentModel;
};