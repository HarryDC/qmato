#include "taskdb.hpp"

const QString TaskDB::backlogName = "Backlog";
const QString TaskDB::iceboxName = "Icebox";
const QString TaskDB::currentName = "Current";
const QString TaskDB::completedName = "Completed";

TaskDB::TaskDB(const QVector<QString> defaultLists, QObject* parent) : QObject(parent)
{
    for (const auto& name : defaultLists) {
        m_tasks[name] = {};
    }
}

void TaskDB::add(const QString& queueName, Task task)
{
    m_tasks[queueName].push_back(task);
}

const QVector<Task>& TaskDB::tasks(const QString& queueName)
{
    return m_tasks[queueName];
}

void TaskDB::remove(const QString& queueName, const Task& task)
{
    auto& tasks = m_tasks[queueName];
    tasks.removeOne(task);
}

void TaskDB::remove(const QString& queueName, const int id) {
    auto& tasks = m_tasks[queueName];
    tasks.removeIf([id](const auto& item) {return item.id == id; });
}

void TaskDB::move(const QString& source, const QString& target, const Task& task)
{
    remove(source, task);
    add(target, task);
}

void TaskDB::move(const QString& source, const QString& target, const int id)
{
    auto& tasks = m_tasks[source];
    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const auto& item) {
        return item.id == id;
        });
    if (it != tasks.end()) return;
    else {
        remove(source, *it);
        add(target, *it);
    }
}


