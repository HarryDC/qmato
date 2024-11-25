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

#pragma once

#include <QtCore>
#include <QTimer>
#include <QJsonValue>

#include <vector>

// Internally keeps seconds
// Timer runs on milliseconds
class TomatoTimer : public QObject {
    Q_OBJECT

public:  

    enum class PeriodType {
        Work,
        ShortBreak,
        LongBreak,
    };

    TomatoTimer(QObject* parent = nullptr);
    TomatoTimer(const QJsonValue& data, QObject* parent = nullptr);

    // Serialisation
    QJsonValue toJson();


    void start();
    void stop();
    void toggle();
    bool isActive() const;


    // Time in seconds
    void setPeriodsSeconds(
        int workPeriod,
        int shortBreakPeriod, 
        int shortBreakRepeat, 
        int longBreakPeriod);

    void setWorkPeriod(int workPeriod);

    void setAutoAdvance(bool val) { m_autoAdvance = val; }
    bool doesAutoAdvance() const { return m_autoAdvance; }

    std::vector<int> intervals() const;

    // Time in seconds
    int remainingTime() const;

    int currentIntervalTime() const;

    const int workPeriod() const noexcept {
        return m_workPeriod;
    }

    const int shortBreakPeriod() const noexcept {
        return m_shortBreakPeriod;
    }

    const int shortBreakRepeat() const noexcept {
        return m_shortBreakRepeat;
    }

    const int longBreakPeriod() const noexcept {
        return m_longBreakPeriod;
    }


    PeriodType currentIntervalType() const noexcept;


signals:
    void timeout();

private slots:
    void onLocalTimeOut();

private:
    void updateIntervals();

    // Default Times in seconds
    int m_workPeriod{ 25 * 60};
    int m_shortBreakPeriod{ 5 * 60 };
    int m_shortBreakRepeat{ 3 };
    int m_longBreakPeriod{ 15 * 60 };

    int m_currentInterval = 0;
    bool m_autoAdvance = false;
    std::vector<int> m_intervals;
    QTimer m_timer;
};
