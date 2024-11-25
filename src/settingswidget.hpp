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

#include "ui_settingswidget.h"

#include "tomatotimer.hpp"

// Shows times in minutes 
class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget* parent = nullptr);

    void setTimer(TomatoTimer* timer) {
        m_tomatotimer = timer;
        reset(false);
    }

signals:
    void updated();

public slots:
    void apply(bool);
    void reset(bool);

private:
    Ui::SettingsWidget ui;
    TomatoTimer* m_tomatotimer = nullptr;
};