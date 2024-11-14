#include "timerwidget.hpp"

#include <format>

TimerWidget::TimerWidget(QWidget* parent) : QWidget(parent)
{
    ui.setupUi(this);
    connect(&m_timer, &QTimer::timeout, this, &TimerWidget::updateDisplay);
    m_timer.setInterval(500);
    connect(ui.startButton, &QPushButton::clicked, this, &TimerWidget::toggle);
    connect(m_tomatotimer, &TomatoTimer::timeout, this, &TimerWidget::intervalTimedOut);
}

void TimerWidget::updateDisplay() {
    int interval = m_tomatotimer->remainingTime();
    int secs = interval % 60;
    interval = interval / 60;
    int mins = interval % 60;

    ui.timeLabel->setText(std::format("{}:{}", mins, secs).c_str());
}

void TimerWidget::start()
{
    m_tomatotimer->start();
    m_timer.start();
    m_isRunning = true;
    ui.startButton->setText(tr("Stop"));
}

void TimerWidget::stop()
{
    m_tomatotimer->stop();
    m_timer.stop();
    m_isRunning = false;
    ui.startButton->setText(tr("Start"));
}

void TimerWidget::toggle(bool checked) {
    if (m_isRunning) {
        stop();
    }
    else {
        start();
    }
}

void TimerWidget::intervalTimedOut() {
    // Play Sound
    // Flash Screen
}

