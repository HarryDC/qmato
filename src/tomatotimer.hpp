#pragma once

#include <QtCore>
#include <QTimer>

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

    void start();
    void stop();
    void toggle();


    // Time in seconds
    void setTimesSeconds(
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
    int m_shortBreakRepeat{ 3 * 60 };
    int m_longBreakPeriod{ 15 * 60 };

    int m_currentInterval = 0;
    bool m_autoAdvance = false;
    std::vector<int> m_intervals;
    QTimer m_timer;
};
