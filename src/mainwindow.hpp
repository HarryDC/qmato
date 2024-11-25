#pragma once

#include "ui_mainwindow.h"

#include <QTimer>

#include "tomatotimer.hpp"
#include "taskdb.hpp"
#include "tasktablemodel.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:

private:
    Ui::MainWindow ui;
    TomatoTimer m_tomatoTimer;
    TaskDB m_taskdb;
    TaskTableModel m_taskModel;
};