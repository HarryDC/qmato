#include "mainwindow.hpp"

#include <format>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.timerWidget->setTimer(&m_tomatoTimer);
    ui.settingsWidget->setTimer(&m_tomatoTimer);
    connect(ui.settingsWidget, &SettingsWidget::updated, ui.timerWidget, &TimerWidget::timerUpdated);
}
