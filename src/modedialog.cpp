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

#include "modedialog.h"
#include "ui_modedialog.h"

#include <iostream>

#include <QtGui>

ModeDialog::ModeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModeDialog)
{
    ui->setupUi(this);

    connect(ui->realTimeButton, SIGNAL(pressed(void)), this, SLOT(realTimeButtonPressed(void)));
    connect(ui->loadButton, SIGNAL(pressed(void)), this, SLOT(loadButtonPressed(void)));
}

ModeDialog::~ModeDialog()
{
    delete ui;
}


void ModeDialog::loadButtonPressed(){

    this->close();

    emit setMode(RECORDED_MODE);
}


void ModeDialog::realTimeButtonPressed(){
    this->close();

    emit setMode(REAL_TIME_MODE);
}
