#include "timerwidget.hpp"

#include <QAudioDevice>
#include <QMediaDevices>

#include <format>

namespace {
const QMap<TomatoTimer::PeriodType, QVector<QString>> motivationText {
        {TomatoTimer::PeriodType::Work, {"Get ready to do some work", "Keep focusing"}},
        {TomatoTimer::PeriodType::ShortBreak, {"Get ready for a short break", "Just relax"}},
        {TomatoTimer::PeriodType::LongBreak, {"Get ready for a long break", "Just relax"}}
    };
}

TimerWidget::TimerWidget(QWidget* parent) : QWidget(parent)
{
    ui.setupUi(this);
    connect(&m_timer, &QTimer::timeout, this, &TimerWidget::updateDisplay);
    m_timer.setInterval(500);
    connect(ui.startButton, &QPushButton::clicked, this, &TimerWidget::toggle);

    m_ring.setSource(QUrl("qrc:/resources/audio/kitchen-ring.wav"));
    m_ring.setVolume(1.0);
}

void TimerWidget::setTimer(TomatoTimer* timer)
{
    if (m_tomatotimer != nullptr) {
        disconnect(m_tomatotimer, &TomatoTimer::timeout, this, &TimerWidget::intervalTimedOut);
    }
    m_tomatotimer = timer;
    if (m_tomatotimer != nullptr) {
        connect(m_tomatotimer, &TomatoTimer::timeout, this, &TimerWidget::intervalTimedOut);
        connect(m_tomatotimer, &TomatoTimer::timeout, &m_ring, &QSoundEffect::play);
        ui.timeDisplay->setTotalTime(m_tomatotimer->currentIntervalTime());
        updateText();
    }
}

void TimerWidget::setTaskDB(TaskDB* taskdb)
{
    m_taskdb = taskdb;
    if (m_taskdb != nullptr) {
        updateTasks();
    }
}

void TimerWidget::updateDisplay() {
    int interval = m_tomatotimer->remainingTime();
    ui.timeDisplay->setRemainingTime(interval);
}

void TimerWidget::start()
{
    m_tomatotimer->start();
    m_timer.start();
    ui.timeDisplay->setTotalTime(m_tomatotimer->currentIntervalTime());
    m_isRunning = true;
    ui.startButton->setText(tr("Stop"));
    updateText();
}

void TimerWidget::stop()
{
    m_tomatotimer->stop();
    m_timer.stop();
    m_isRunning = false;
    ui.startButton->setText(tr("Start"));
    ui.timeDisplay->setTotalTime(m_tomatotimer->currentIntervalTime());
    updateText();
}

void TimerWidget::toggle(bool checked) {
    if (m_isRunning) {
        stop();
    }
    else {
        start();
    }
}

void TimerWidget::timerUpdated()
{
    ui.timeDisplay->setTotalTime(m_tomatotimer->currentIntervalTime());
}

void TimerWidget::intervalTimedOut() {

}

void TimerWidget::updateTasks()
{
    if (m_taskdb == nullptr) return;
    const auto& tasks = m_taskdb->tasks(TaskDB::currentName);
    ui.taskBox->clear();
    for (const auto& task : tasks) {
        ui.taskBox->addItem(task.name);
    }
}

void TimerWidget::updateText()
{
    if (m_tomatotimer == nullptr) return;
    auto periodType = m_tomatotimer->currentIntervalType();
    auto index = m_tomatotimer->isActive() ? 1 : 0;
    ui.previewLabel->setText(motivationText[periodType][index]);
}

