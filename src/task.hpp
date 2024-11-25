#pragma once

#include <QString>

struct Task {
    static const QString backlogName;
    static const QString iceboxName;
    static const QString currentName;
    static const QString completedName;

    static constexpr int nameColumn{ 0 };
    static constexpr int tableColumn{ 1 };
    static constexpr int columnCount{ 2 };

    int id;
    QString name;
    QString table = Task::backlogName;
    int estimate = 0;
    int elapsedTime = 0;

    bool operator==(const Task& other) const {
        return id == other.id;
    }

    bool operator==(const int otherId) const {
        return id == otherId;
    }

    static int newId() {
        return m_maxId++;
    }



private:
    static int m_maxId;
};