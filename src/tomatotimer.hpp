#pragma once

#include <QtCore>
#include <QTimer>

#include <vector>

class TomatoTimer : public QObject {
    Q_OBJECT

public: 
    TomatoTimer(QObject* parent = nullptr);

    void start();
    void stop();
    void toggle();

    void setBreaks(const std::vector<int>& breaks);

    void setWorkPeriod(int workPeriod);

    void setAutoAdvance(bool val) { m_autoAdvance = val; }
    bool doesAutoAdvance() const { return m_autoAdvance; }

    std::vector<int> intervals() const;

    int remainingTime() const;

    int currentIntervalTime() const;

signals:
    void timeout();

private slots:
    void onLocalTimeOut();

private:
    void updateIntervals();

    std::vector<int> m_breaks{ 5 * 60000, 5 * 60000, 15 * 60000 };
    int m_workPeriod{ 25 * 600000 };
    int m_currentInterval = 0;
    bool m_autoAdvance = false;
    std::vector<int> m_intervals;
    QTimer m_timer;
};