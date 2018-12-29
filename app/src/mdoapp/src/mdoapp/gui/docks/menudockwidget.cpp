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


#include "menudockwidget.h"
#include "ui_menudockwidget.h"

#include <QTreeWidgetItem>

MenuDockWidget::MenuDockWidget(QWidget *parent) :
    DsDockWidget(),
    ui(new Ui::MenuDockWidget)
{
    ui->setupUi(this);
    setWindowTitle(QApplication::translate("MenuDockWidget", "Tools", 0));
    setAllowedAreas(Qt::AllDockWidgetAreas);
    setFeatures(QDockWidget::AllDockWidgetFeatures);
    ui->menuTreeWidget->setColumnCount(1);
    QList<QTreeWidgetItem *> items;
    items.append(new QTreeWidgetItem((QTreeWidget *)0, QStringList("Dashboard")));
    items.append(new QTreeWidgetItem((QTreeWidget *)0, QStringList("Editor")));
    items.append(new QTreeWidgetItem((QTreeWidget *)0, QStringList("History")));
    ui->menuTreeWidget->insertTopLevelItems(0, items);
}

MenuDockWidget::~MenuDockWidget()
{
    delete ui;
}

QTreeWidget *MenuDockWidget::getMenuTree()
{
    return ui->menuTreeWidget;
}
