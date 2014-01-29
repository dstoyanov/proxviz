/*
 * Copyright 2013 Dimo Stoyanov
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


/**
 *  @file modedialog.h
 *  @author Dimo Stoyanov
 *  @brief The first dialog that appears on the screen. The choice between
 *  real time visualization and prerecorded dataset is made here.
 */
#ifndef MODEDIALOG_H
#define MODEDIALOG_H

#include <QDialog>

enum mode_type {DEFAULT_MODE, REAL_TIME_MODE, RECORDED_MODE};

namespace Ui {
class ModeDialog;
}

class ModeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModeDialog(QWidget *parent = 0);
    ~ModeDialog();

private:
    Ui::ModeDialog *ui;

private slots:
    void realTimeButtonPressed();
    void loadButtonPressed();


signals:
    void setMode(mode_type);
};

#endif // MODEDIALOG_H
