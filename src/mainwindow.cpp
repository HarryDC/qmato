#include "mainwindow.hpp"

#include <format>

MainWindow::MainWindow(QWidget* parent) : 
    QMainWindow(parent),
    m_tomatoTimer(this),
    m_taskdb({TaskDB::currentName, TaskDB::completedName}, this)
{
    ui.setupUi(this);
    {
        Task t = {.id = 1, .name = "Task1"};
        m_taskdb.add(TaskDB::currentName, t);
    }
    {
        Task t = {.id = 2,  .name = "Task2" };
        m_taskdb.add(TaskDB::currentName, t);
    }

    ui.timerWidget->setTimer(&m_tomatoTimer);
    ui.timerWidget->setTaskDB(&m_taskdb);
    ui.settingsWidget->setTimer(&m_tomatoTimer);
    ui.tasksWidget->setTaskDB(&m_taskdb);
    connect(ui.settingsWidget, &SettingsWidget::updated, ui.timerWidget, &TimerWidget::timerUpdated);
}
