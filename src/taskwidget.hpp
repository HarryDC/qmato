#pragma once
#include "ui_taskwidget.h"

#include <QWidget>

#include "taskdb.hpp"

class TaskWidget : public QWidget {
    Q_OBJECT
public:
    TaskWidget(QWidget* parent = nullptr) : QWidget(parent) {};

    void setTaskDB(TaskDB* taskdb) {
        m_taskdb = taskdb;
    }

private:
    Ui::TaskWidget ui;
    TaskDB* m_taskdb = nullptr;
};