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

#pragma once

#include <QString>
#include <QJsonValue>

struct Task {
    static const QString backlogName;
    static const QString iceboxName;
    static const QString currentName;
    static const QString completedName;

    Task() : id(Task::newId()) {}

    Task(const QJsonValue& obj);
    QJsonValue toJson() const;

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
        return ++m_maxId;
    }



private:
    static int m_maxId;
};