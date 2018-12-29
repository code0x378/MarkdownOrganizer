/*
* Markdown Organizer
* Copyright (C) 2016-2018 JeffSmithDev
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "helpwindow.h"
#include "ui_helpwindow.h"

#include <mdoapp/gui/widgets/helpwidget.h>

HelpWindow::HelpWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HelpWindow)
{
    ui->setupUi(this);

    helpWidget = new HelpWidget();
    ui->verticalLayout_2->addWidget(helpWidget);
}

HelpWindow::~HelpWindow()
{
    delete ui;
}
