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
    return parent.isValid() ? 0 : Task::columnCount;
}

QVariant TaskTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case Task::nameColumn:
            return tr("Task");
        case Task::tableColumn:
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
        case Task::nameColumn:
            return task.name;
        case Task::tableColumn:
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
        m_tasks.insert(position, { Task::newId(), QString() });

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
        auto contact = m_tasks.value(row);

        switch (index.column()) {
        case Task::nameColumn:
            contact.name = value.toString();
            break;
        default:
            return false;
        }
        m_tasks.replace(row, contact);
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
