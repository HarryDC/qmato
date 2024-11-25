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

#include "settingswidget.hpp"

SettingsWidget::SettingsWidget(QWidget* parent) : QWidget(parent)
{
    ui.setupUi(this);
    connect(ui.applyButton, &QPushButton::clicked, this, &SettingsWidget::apply);
    connect(ui.resetButton, &QPushButton::clicked, this, &SettingsWidget::reset);
}

void SettingsWidget::apply(bool) {
    m_tomatotimer->setPeriodsSeconds(
        ui.workTimeBox->value() * 60,
        ui.shortBreakTimeBox->value() * 60,
        ui.shortBreakRepeatBox->value(),
        ui.longBreakTimeBox->value() * 60
    );
    m_tomatotimer->setAutoAdvance(ui.autoAdvanceCheckBox->isChecked());
    emit updated();
}

void SettingsWidget::reset(bool) {
    if (m_tomatotimer == nullptr) return;

    ui.workTimeBox->setValue(m_tomatotimer->workPeriod() / 60);
    ui.shortBreakTimeBox->setValue(m_tomatotimer->shortBreakPeriod() / 60);
    ui.shortBreakRepeatBox->setValue(m_tomatotimer->shortBreakRepeat());
    ui.longBreakTimeBox->setValue(m_tomatotimer->longBreakPeriod() / 60);
    ui.autoAdvanceCheckBox->setChecked(m_tomatotimer->doesAutoAdvance());
}
