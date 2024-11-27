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

#include "task.hpp"

#include <QJsonObject>

const QString Task::backlogName = "Backlog";
const QString Task::iceboxName = "Icebox";
const QString Task::currentName = "Current";
const QString Task::completedName = "Completed";

int Task::m_maxId = 0;

Task::Task(const QJsonValue& obj) {
    id = obj["id"].toInt();
    name = obj["name"].toString();
    table = obj["table"].toString();
    estimate = obj["estimate"].toInt();
    elapsedTime = obj["elapsedTime"].toInt();

    if (Task::m_maxId < id) {
        Task::m_maxId = id;
    }
}

QJsonValue Task::toJson() const {
    QJsonObject obj;
    obj["id"] = id;
    obj["name"] = name;
    obj["table"] = table;
    obj["estimate"] = estimate;
    obj["elapsedTime"] = elapsedTime;

    return QJsonValue(obj);
}
