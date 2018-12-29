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

#ifndef DASHBOARDTOOLWIDGET_H
#define DASHBOARDTOOLWIDGET_H

#include <QWidget>

namespace Ui {
class DashboardToolWidget;
}

class DashboardToolWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardToolWidget(QWidget *parent = 0);
    ~DashboardToolWidget();

private:
    Ui::DashboardToolWidget *ui;
};

#endif // DASHBOARDTOOLWIDGET_H
