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

#include "tasktablemodel.hpp"

TaskTableModel::TaskTableModel(QObject* parent) : QAbstractTableModel(parent) {}

TaskTableModel::TaskTableModel(const QVector<Task>& tasks, QObject* parent) :
    m_tasks(tasks),
    QAbstractTableModel(parent) {}

int TaskTableModel::rowCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : m_tasks.size();
}

int TaskTableModel::columnCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : TaskTableModel::columns;
}

QVariant TaskTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case nameColumn:
            return tr("Task");
        case tableColumn:
            return tr("Table");
        default:
            break;
        }
    }
    return QVariant();
}

QVariant TaskTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_tasks.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto& task = m_tasks.at(index.row());

        switch (index.column()) {
        case nameColumn:
            return task.name;
        case tableColumn:
            return task.table;
        default:
            break;
        }
    }
    return QVariant();
}

bool TaskTableModel::insertRows(int position, int rows, const QModelIndex&)
{
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        m_tasks.insert(position, {});

    endInsertRows();
    return true;
}

bool TaskTableModel::insertRow(int position, const Task& task) {
    beginInsertRows(QModelIndex(), position, position);
    m_tasks.insert(position, task);
    endInsertRows();
    return true;
}

bool TaskTableModel::removeRows(int position, int rows, const QModelIndex&)
{
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        m_tasks.removeAt(position);

    endRemoveRows();
    return true;
}

bool TaskTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        const int row = index.row();
        auto task = m_tasks.value(row);

        switch (index.column()) {
        case nameColumn:
            task.name = value.toString();
            break;
        case tableColumn:
            task.table = value.toString();
            break;
        default:
            return false;
        }
        m_tasks.replace(row, task);
        emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole });

        return true;
    }
    return false;
}

Qt::ItemFlags TaskTableModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

const QVector<Task>& TaskTableModel::getTasks() const
{
    return m_tasks;
}

void TaskTableModel::setTasks(QVector<Task> tasks)
{
    beginResetModel();
    m_tasks = std::move(tasks);
    endResetModel();
}
