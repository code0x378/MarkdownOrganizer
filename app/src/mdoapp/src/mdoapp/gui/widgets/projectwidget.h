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

#ifndef PROJECTWIDGET_H
#define PROJECTWIDGET_H

#include <QFileSystemModel>
#include <QWidget>

namespace Ui {
class ProjectWidget;
}

class ProjectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectWidget(QWidget *parent = 0);
    ~ProjectWidget();
Q_SIGNALS:
    void fileSelected(QString filePath);
    void projectChanged(const QString projectName);

public Q_SLOTS:
    void changeProject();

private Q_SLOTS:
    void loadFile(const QModelIndex index);
    void filterFiles();

private:
    Ui::ProjectWidget *ui;
    QFileSystemModel *model;
    void selectActiveProduct();
};

#endif // PROJECTWIDGET_H
