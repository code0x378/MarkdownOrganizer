/*
* Markdown Organizer
* Copyright (C) 2016-2021 code0x378
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

#ifndef HELPTOOLWIDGET_H
#define HELPTOOLWIDGET_H

#include <QWidget>
#include <QFileSystemModel>

#include <mdoapp/gui/widgets/helpwidget.h>

namespace Ui {
class HelpToolWidget;
}

class HelpToolWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HelpToolWidget(QWidget *parent = 0);
    ~HelpToolWidget();

private:
    Ui::HelpToolWidget *ui;
    HelpWidget *helpWidget;
};

#endif // HELPTOOLWIDGET_H
