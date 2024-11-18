#include "timedisplaywidget.hpp"

void TimeDisplayWidget::paintEvent(QPaintEvent* /* event */)
{
    const int startAngle = 90 * 16;

    const float fraction = static_cast<float>(m_remainingTime) / static_cast<float>(m_totalTime);
    const int arcAngle = 360.0 * 16.0 * fraction;

    QPainter painter(this);
    QPen pen;  // creates a default pen
    int penWidth = 10;
    QRect rect;
    if (width() > height()) {
        int rest = (width() - height()) / 2;
        int dim = height() - penWidth / 2;
        rect = QRect{ rest, penWidth/2, dim, dim};
    }
    else {
        int rest = (height() - width()) / 2;
        int dim = width() - penWidth / 2;
        rect = QRect(penWidth/2, rest, dim, dim);
    }

    pen.setStyle(Qt::SolidLine);
    pen.setWidth(10);
    pen.setBrush(Qt::red);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen);
   
    painter.drawArc(rect, startAngle,arcAngle);
}