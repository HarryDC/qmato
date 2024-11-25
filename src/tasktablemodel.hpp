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

    bool removeRows(int position, int rows, const QModelIndex&);

    bool setData(const QModelIndex& index, const QVariant& value, int role);

    Qt::ItemFlags flags(const QModelIndex& index) const;

    const QVector<Task>& getTasks() const;

    void setTasks(QVector<Task> tasks);

private:
    QVector<Task> m_tasks;
};
