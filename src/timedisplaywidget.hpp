#pragma once

#include <QtWidgets>

class TimeDisplayWidget : public QWidget
{
    Q_OBJECT
public:
    TimeDisplayWidget(QWidget* parent = nullptr) : QWidget(parent) {}

public slots:
    void setTotalTime(int seconds) {
        m_totalTime = seconds;
        m_remainingTime = seconds;
        update();
    }

    void setRemainingTime(int seconds) {
        m_remainingTime = seconds;
        update();
    }

private:
    void paintEvent(QPaintEvent*) override;

    int m_totalTime;
    int m_remainingTime;
};