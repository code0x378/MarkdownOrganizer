/*
* Markdown Organizer
* Copyright (C) 2016-2018 ThoughtLogix
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

#ifndef PROJECTDIALOG_H
#define PROJECTDIALOG_H

#include <QDialog>
#include <QSqlRecord>

class QSqlRelationalTableModel;

namespace Ui {
class ProjectDialog;
}

class ProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectDialog(QWidget *parent = 0);
    ~ProjectDialog();

private slots:
    void addProject();
    void deleteProject();
    void newProject();
    void updateSelectedTabs(const QModelIndex &index);
    void onToggled();
private:
    Ui::ProjectDialog *ui;
    QSqlRelationalTableModel *model;
    void loadProjects();
    void displayPlugins();
};

#endif // PROJECTDIALOG_H
