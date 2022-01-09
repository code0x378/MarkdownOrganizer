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

#ifndef PROJECTDOCKWIDGET_H
#define PROJECTDOCKWIDGET_H

#include <QAction>
#include <QDockWidget>
#include <QFileSystemModel>

#include "mdoapp/gui/docks/mdodockwidget.h"

namespace Ui {
class ProjectDockWidget;
}

class ProjectDockWidget : public DsDockWidget
{
    Q_OBJECT

public:
    explicit ProjectDockWidget(QWidget *parent = 0);
    ~ProjectDockWidget();

signals:
    void fileSelected(QString filePath);
    void fileDeleted(QString filePath);
    void projectChanged(const QString projectName);

public slots:
    void changeProject();

private slots:
    void loadFile(const QModelIndex index);
    void filterFiles();
    void onCustomContextMenu(const QPoint &point);
    void deleteFile();

    void selectFile(const QModelIndex index);
private:
    Ui::ProjectDockWidget *ui;
    QFileSystemModel *model;
    void selectActiveProduct();
    QMenu *contextMenu;
    QAction *deleteAction;
    QString *activeFilePath;
};

#endif // PROJECTDOCKWIDGET_H
