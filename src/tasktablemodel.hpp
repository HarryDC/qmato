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

#include <QAbstractTableModel>

#include "task.hpp"

class TaskTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TaskTableModel(QObject* parent = nullptr);;

    TaskTableModel(const QVector<Task>& tasks, QObject* parent = nullptr);;

    int rowCount(const QModelIndex& parent) const override;

    int columnCount(const QModelIndex& parent) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    QVariant data(const QModelIndex& index, int role) const;

    bool insertRows(int position, int rows, const QModelIndex&);

    bool insertRow(int position, const Task& task);

    bool removeRows(int position, int rows, const QModelIndex&);

    bool setData(const QModelIndex& index, const QVariant& value, int role);

    Qt::ItemFlags flags(const QModelIndex& index) const;

    const QVector<Task>& getTasks() const;

    void setTasks(QVector<Task> tasks);

    static constexpr int idColumn{ 0 };
    static constexpr int nameColumn{ 1 };
    static constexpr int tableColumn{ 2 };
    static constexpr int columns{ 3 };

private:
    QVector<Task> m_tasks;
};
