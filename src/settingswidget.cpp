#include "settingswidget.hpp"

SettingsWidget::SettingsWidget(QWidget* parent) : QWidget(parent)
{
    ui.setupUi(this);
    connect(ui.applyButton, &QPushButton::clicked, this, &SettingsWidget::apply);
    connect(ui.resetButton, &QPushButton::clicked, this, &SettingsWidget::reset);
}

void SettingsWidget::apply(bool) {
    m_tomatotimer->setTimes(
        ui.workTimeBox->value(),
        ui.shortBreakTimeBox->value(),
        ui.shortBreakRepeatBox->value(),
        ui.longBreakTimeBox->value()
    );
    m_tomatotimer->setAutoAdvance(ui.autoAdvanceCheckBox->isChecked());
}

void SettingsWidget::reset(bool) {
    if (m_tomatotimer == nullptr) return;

    ui.workTimeBox->setValue(m_tomatotimer->workPeriod());
    ui.shortBreakTimeBox->setValue(m_tomatotimer->shortBreakPeriod());
    ui.shortBreakRepeatBox->setValue(m_tomatotimer->shortBreakRepeat());
    ui.longBreakTimeBox->setValue(m_tomatotimer->longBreakPeriod());
    ui.autoAdvanceCheckBox->setChecked(m_tomatotimer->doesAutoAdvance());
}
