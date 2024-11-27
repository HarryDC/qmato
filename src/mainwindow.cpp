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

#include "mainwindow.hpp"
#include "task.hpp"

#include <QVector>
#include <QJsonDocument>
#include <format>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    m_tomatoTimer(this)
{
    QVector<Task> tasks;
    ui.setupUi(this);
    {
        Task t;
        t.name = "Task1";
        t.table = Task::currentName;
        tasks.push_back(t);
    }
    {
        Task t;
        t.name = "Task2";
        t.table = Task::currentName;
        tasks.push_back(t);
    }
    {
        Task t;
        t.name = "Task3";
        t.table = Task::completedName;
        tasks.push_back(t);
    }

    // autoload last file here

    m_taskModel.setTasks(tasks);

    connect(ui.actionLoad, &QAction::triggered, this, &MainWindow::loadTasks);
    connect(ui.actionSave, &QAction::triggered, this, &MainWindow::saveTasks);

    ui.timerWidget->setTimer(&m_tomatoTimer);
    ui.timerWidget->setModel(&m_taskModel);
    ui.settingsWidget->setTimer(&m_tomatoTimer);
    ui.tasksWidget->setModel(&m_taskModel);
    connect(ui.settingsWidget, &SettingsWidget::updated, ui.timerWidget, &TimerWidget::timerUpdated);
}

void MainWindow::loadTasks() {
    auto filename = QFileDialog::getOpenFileName(this,
        tr("Open Tasks File"), "", tr("Json File (*.json)"));
    auto result = loadJson(filename);

    if (result.type() == QVariant::String) {
        QMessageBox::warning(this, "Error during Loading", result.toString());
    }
    else {
        auto doc = result.toJsonDocument();
        if (doc.isObject()) {
            auto jsontasks = doc["tasks"].toArray();
            QVector<Task> tasks;
            for (const auto& obj : jsontasks) {
                tasks.push_back(Task(obj));
            }
            m_taskModel.setTasks(tasks);
        }
    }
}

void MainWindow::saveTasks() {
    auto filename = QFileDialog::getSaveFileName(this,
        tr("Save Tasks File"), "", tr("Json File (*.json)"));
    
    const auto& tasks = m_taskModel.getTasks();
    QJsonArray jsontasks;
    for (const auto& task : tasks) {
        jsontasks.push_back(task.toJson());
    }
    QJsonObject obj;
    obj["tasks"] = jsontasks;
    auto result = saveJson(QJsonDocument(obj), filename);
    if (result.type() == QVariant::String) {
        QMessageBox::warning(this, "Error during Saving", result.toString());
    }
}

QVariant MainWindow::loadJson(const QString& filename)
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString message = QString("Could not open file %1\nError:%2")
            .arg(filename).arg(file.errorString());
        qWarning() << message;
        return message;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        auto message = QString("Could not parse JSON: %1\nError at offset:%2")
            .arg(parseError.errorString()).arg(parseError.offset);
        qWarning() << message;
        return message;
    }

    return jsonDoc;
}

QVariant MainWindow::saveJson(const QJsonDocument& doc, const QString& filename)
{
    QSaveFile file(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        auto message = QString("Could not open file for writing: %1. Error: %2")
            .arg(filename).arg(file.errorString());
        qWarning() << message;
        return message;
    }

    QByteArray jsonData = doc.toJson(QJsonDocument::Indented);
    qint64 bytesWritten = file.write(jsonData);

    if (bytesWritten == -1) {
        auto message = QString("Failed to write data to file: %1. Error: %2")
            .arg(filename).arg(file.errorString());
        qWarning() << message;
        file.cancelWriting();
        return message;
    }

    if (!file.commit()) {
        auto message = QString("Failed to save file: %1").arg(filename);
        qWarning() << message;
        return message;
    }

    return true;
}