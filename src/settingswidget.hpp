#pragma once

#include "ui_settingswidget.h"

#include "tomatotimer.hpp"

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget* parent = nullptr);

    void setTimer(TomatoTimer* timer) {
        m_tomatotimer = timer;
        reset(false);
    }


public slots:
    void apply(bool);
    void reset(bool);

private:
    Ui::SettingsWidget ui;
    TomatoTimer* m_tomatotimer = nullptr;
};