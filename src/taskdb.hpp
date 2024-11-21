#pragma once

#include <QObject>
#include <QString>
#include <QMap>
#include <QVector>

struct Task {
    int id;
    QString name;
    int estimate = 0;
    int elapsedTime = 0;

    bool operator==(const Task& other) const {
        return id == other.id;
    }

    bool operator==(const int otherId) const {
        return id == otherId;
    }
};

class TaskDB : public QObject {
    Q_OBJECT

public:
    static const QString backlogName;
    static const QString iceboxName;
    static const QString currentName;
    static const QString completedName;

    TaskDB(const QVector<QString> defaultLists = {}, QObject* parent = nullptr);

    void add(const QString& queueName, Task task);
    const QVector<Task>& tasks(const QString& queueName);
    void remove(const QString& queueName, const Task& id);
    void remove(const QString& queueName, const int id);
    void move(const QString& source, const QString& target, const Task& task);
    void move(const QString& source, const QString& target, const int id);
private:
    QMap<QString, QVector<Task>> m_tasks;
};