#include "mainwindow.hpp"
#include "task.hpp"

#include <QVector>
#include <format>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    m_tomatoTimer(this),
    m_taskdb({ TaskDB::currentName, TaskDB::completedName }, this)
{
    QVector<Task> tasks;
    ui.setupUi(this);
    {
        Task t = {.id = 1, .name = "Task1", .table = Task::currentName};
        m_taskdb.add(TaskDB::currentName, t);
        tasks.push_back(t);
    }
    {
        Task t = {.id = 2,  .name = "Task2", .table = Task::currentName };
        m_taskdb.add(TaskDB::currentName, t);
        tasks.push_back(t);
    }
    {
        Task t = { .id = 3,  .name = "Task2", .table = Task::backlogName};
        m_taskdb.add(TaskDB::currentName, t);
        tasks.push_back(t);
    }

    m_taskModel.setTasks(tasks);

    ui.timerWidget->setTimer(&m_tomatoTimer);
    ui.timerWidget->setModel(&m_taskModel);
    ui.settingsWidget->setTimer(&m_tomatoTimer);
    ui.tasksWidget->setTaskDB(&m_taskdb);
    connect(ui.settingsWidget, &SettingsWidget::updated, ui.timerWidget, &TimerWidget::timerUpdated);
}
