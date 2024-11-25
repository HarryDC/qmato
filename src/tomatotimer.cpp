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

#include "tomatotimer.hpp"

TomatoTimer::TomatoTimer(QObject* parent) : QObject(parent) {
    m_timer.setSingleShot(true);
    connect(&m_timer, &QTimer::timeout, this, &TomatoTimer::onLocalTimeOut);
    updateIntervals();
}

TomatoTimer::TomatoTimer(const QJsonValue& data, QObject* parent)
{
    if (!data.isObject()) {
        qCritical() << "Tomatotimes json data is not an object";
        return;
    }

    int workPeriod = data["work_period"].toInt();
    int shortBreakPeriod = data["short_break_period"].toInt();
    int shortBreakRepeat = data["short_break_repeat"].toInt();
    int longBreakPeriod = data["long_break_period"].toInt();
    bool autoAdvance = data["auto_advance"].toBool();
    setAutoAdvance(autoAdvance);
    setPeriodsSeconds(workPeriod, shortBreakPeriod, shortBreakRepeat, longBreakPeriod);
}

QJsonValue TomatoTimer::toJson()
{
    QJsonObject data;
    data["work_period"] = m_workPeriod;
    data["short_break_period"] = m_shortBreakPeriod;
    data["short_break_repeat"] = m_shortBreakRepeat;
    data["long_break_period"] = m_longBreakPeriod;
    data["auto_advance"] = m_autoAdvance;

    return QJsonValue(data);
}


void TomatoTimer::start()
{
    m_timer.setInterval(m_intervals[m_currentInterval] * 1000);
    m_timer.start();
}

void TomatoTimer::stop()
{
    m_timer.stop();
    m_currentInterval = (m_currentInterval + 1) % m_intervals.size();
}

void TomatoTimer::toggle()
{
}

bool TomatoTimer::isActive() const
{
    return m_timer.isActive();
}

void TomatoTimer::setPeriodsSeconds(int workPeriod, int shortBreakPeriod, int shortBreakRepeat, int longBreakPeriod)
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

TomatoTimer::PeriodType TomatoTimer::currentIntervalType() const noexcept {
    int period = m_intervals[m_currentInterval];
    if (period == m_workPeriod) return PeriodType::Work;
    if (period == m_shortBreakPeriod) return PeriodType::ShortBreak;
    if (period == m_longBreakPeriod) return PeriodType::LongBreak;
    return PeriodType::Work;
}

std::vector<int> TomatoTimer::intervals() const { return m_intervals; }

int TomatoTimer::remainingTime() const {
    if (m_timer.isActive()) {
        return m_timer.remainingTime() / 1000;
    }
    else {
        return m_intervals[m_currentInterval];
    }
}

int TomatoTimer::currentIntervalTime() const
{
    return m_intervals[m_currentInterval];
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