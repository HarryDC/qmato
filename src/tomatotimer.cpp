#include "tomatotimer.hpp"


TomatoTimer::TomatoTimer(QObject* parent) : QObject(parent) {
    m_timer.setSingleShot(true);
    connect(&m_timer, &QTimer::timeout, this, &TomatoTimer::onLocalTimeOut);
    updateIntervals();
}

void TomatoTimer::start()
{
    m_timer.setInterval(m_intervals[m_currentInterval] * 1000 * 60);
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

void TomatoTimer::setTimes(int workPeriod, int shortBreakPeriod, int shortBreakRepeat, int longBreakPeriod)
{
    m_workPeriod = workPeriod;
    m_shortBreakPeriod = shortBreakPeriod;
    m_shortBreakRepeat = shortBreakRepeat;
    m_longBreakPeriod = longBreakPeriod;
    updateIntervals();
}

void TomatoTimer::setWorkPeriod(int workPeriod) {
    m_workPeriod = workPeriod;
    updateIntervals();
}

std::vector<int> TomatoTimer::intervals() const { return m_intervals; }

int TomatoTimer::remainingTime() const {
    return m_timer.remainingTime() / 1000;
}

int TomatoTimer::currentIntervalTime() const
{
    return m_timer.interval();
}

void TomatoTimer::updateIntervals() {
    m_intervals.clear();
    for (int i = 0; i < m_shortBreakRepeat; ++i) {
        m_intervals.push_back(m_workPeriod);
        m_intervals.push_back(m_shortBreakPeriod);
    }
    m_intervals.push_back(m_workPeriod);
    m_intervals.push_back(m_longBreakPeriod);
}

void TomatoTimer::onLocalTimeOut() {
    emit timeout();
    if (m_autoAdvance) {
        start();
    }
}