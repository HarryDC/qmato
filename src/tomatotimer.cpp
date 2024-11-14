#include "tomatotimer.hpp"


TomatoTimer::TomatoTimer(QObject* parent) : QObject(parent) {
    m_timer.setSingleShot(true);
    connect(&m_timer, &QTimer::timeout, this, &TomatoTimer::onLocalTimeOut);
    updateIntervals();
}

void TomatoTimer::start()
{
    m_timer.setInterval(m_intervals[m_currentInterval]);
    m_timer.start();
    m_currentInterval = (m_currentInterval + 1) % m_intervals.size();
}

void TomatoTimer::stop()
{
    m_timer.stop();
}

void TomatoTimer::toggle()
{
}

void TomatoTimer::setBreaks(const std::vector<int>& breaks) {
    m_breaks = breaks;
    updateIntervals();
}

void TomatoTimer::setWorkPeriod(int workPeriod) {
    m_workPeriod = workPeriod;
    updateIntervals();
}

std::vector<int> TomatoTimer::intervals() const { return m_intervals; }

int TomatoTimer::remainingTime() const {
    return m_timer.remainingTime();
}

int TomatoTimer::currentIntervalTime() const
{
    return m_timer.interval();
}

void TomatoTimer::updateIntervals() {
    m_intervals.clear();
    for (auto breakTime : m_breaks) {
        m_intervals.push_back(m_workPeriod);
        m_intervals.push_back(breakTime);
    }
}

void TomatoTimer::onLocalTimeOut() {
    emit timeout();
    if (m_autoAdvance) {
        start();
    }
}