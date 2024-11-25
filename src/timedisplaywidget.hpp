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