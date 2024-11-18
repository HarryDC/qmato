#pragma once

#include <QtWidgets>

class TimeDisplayWidget : public QWidget
{
    Q_OBJECT
public:
    TimeDisplayWidget(QWidget* parent = nullptr);

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

    QPen m_circlePen;
    QPen m_textPen;
    QFont m_font;

    int m_totalTime = 0;
    int m_remainingTime = 0;
};