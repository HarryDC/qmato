#include "timedisplaywidget.hpp"

TimeDisplayWidget::TimeDisplayWidget(QWidget* parent) : 
    QWidget(parent)
{

    int penWidth = 10;

    m_circlePen.setStyle(Qt::SolidLine);
    m_circlePen.setWidth(10);
    m_circlePen.setBrush(Qt::red);
    m_circlePen.setCapStyle(Qt::FlatCap);
    m_circlePen.setJoinStyle(Qt::RoundJoin);

    m_font.setBold(true);

}

void TimeDisplayWidget::paintEvent(QPaintEvent* /* event */)
{
    const int startAngle = 90 * 16;

    const float fraction = static_cast<float>(m_remainingTime) / static_cast<float>(m_totalTime);
    const int arcAngle = 360.0 * 16.0 * fraction;

    int penWidth = m_circlePen.width();

    QRect rect;
    if (width() > height()) {
        int rest = (width() - height()) / 2;
        int dim = height() - penWidth;
        rect = QRect{ rest, penWidth/2, dim, dim};
    }
    else {
        int rest = (height() - width()) / 2;
        int dim = width() - penWidth;
        rect = QRect(penWidth/2, rest, dim, dim);
    }

    QPainter painter(this);
    
    m_font.setPixelSize(rect.height() / 4);
    painter.setFont(m_font);
    
    painter.setPen(m_circlePen);

    painter.drawArc(rect, startAngle, arcAngle);

    int secs = m_remainingTime % 60;
    int mins = m_remainingTime / 60;

    QString text = QString("%1:%2").arg(mins, 2, 10, QChar('0')).arg(secs, 2, 10, QChar('0'));
    QFontMetrics fm = painter.fontMetrics();
    int w = fm.horizontalAdvance("00:00");
    QPoint pos = QPoint(rect.x() + rect.width() / 2 - w / 2, rect.y() + rect.height() / 2 + (m_font.pixelSize() / 2 - 10));
    
    painter.setPen(m_textPen);
    painter.drawText(pos, text);
}

