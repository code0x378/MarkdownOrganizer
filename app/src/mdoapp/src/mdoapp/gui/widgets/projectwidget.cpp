/*
* Markdown Organizer
* Copyright (C) 2016-2020 code0x378
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

#include "projectwidget.h"
#include "ui_projectwidget.h"

#include <QFileSystemModel>
#include <QHeaderView>
#include <QMessageBox>
#include <QTextStream>

#include "mdocore/mdoapplication.h"
#include "mdocore/logmanager.h"
#include "mdocore/util/qtutils.h"
#include "mdoapp/gui/appmainwindow.h"

ProjectWidget::ProjectWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectWidget)
{
    ui->setupUi(this);
    ui->treeViewProject->setRootIsDecorated(false);
    ui->treeViewProject->setExpandsOnDoubleClick(false);

    QHash<QString, Project *>::iterator i;
    for (i = APP->getProjects()->begin(); i != APP->getProjects()->end(); ++i)
        ui->comboBoxProjects->addItem((i.value()->getName()));

    model = new QFileSystemModel;
    model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    model->setRootPath(APP->getActiveProject()->getWorkingDirectory());
    ui->treeViewProject->setModel(model);
    ui->treeViewProject->setColumnHidden(1, true);
    ui->treeViewProject->setColumnHidden(2, true);
    ui->treeViewProject->setColumnHidden(3, true);
    ui->treeViewProject->setRootIndex(model->index(
                                          APP->getActiveProject()->getWorkingDirectory()));

    VERIFY(connect(ui->comboBoxProjects, SIGNAL(currentIndexChanged(int)), this,
                   SLOT(changeProject())));
    VERIFY(connect(ui->treeViewProject, SIGNAL(clicked(const QModelIndex &)), this,
                   SLOT(loadFile(const QModelIndex &))));
    VERIFY(connect(ui->filterLineEdit, SIGNAL(textChanged(const QString &)), this,
                   SLOT(filterFiles())));
    selectActiveProduct();
}

ProjectWidget::~ProjectWidget()
{
    delete ui;
}

void ProjectWidget::changeProject()
{
    QString projectName = ui->comboBoxProjects->currentText();
    APP->setActiveProject(APP->getProjects()->value(projectName));
    ui->treeViewProject->setRootIndex(model->setRootPath(
                                          APP->getActiveProject()->getWorkingDirectory()));
    APP->getActiveProject()->setCurrentDirectory(
        APP->getActiveProject()->getWorkingDirectory());
    model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    emit projectChanged(projectName);
    LOG_INFO("Project changed:" + projectName);
}

void ProjectWidget::selectActiveProduct()
{
    QString projectName = APP->getActiveProject()->getName();
    ui->treeViewProject->setRootIndex(model->setRootPath(
                                          APP->getActiveProject()->getWorkingDirectory()));;
    ui->comboBoxProjects->setCurrentIndex(ui->comboBoxProjects->findText(
                                              projectName));
    APP->getActiveProject()->setCurrentDirectory(
        APP->getActiveProject()->getWorkingDirectory());
    model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    emit projectChanged(projectName);
}

void ProjectWidget::loadFile(const QModelIndex index)
{
    QString filePath = model->fileInfo(index).absoluteFilePath();

    QFileInfo fileInfo(filePath);
    if (fileInfo.isDir()) {
        if (filePath + QDir::separator() ==
                APP->getActiveProject()->getWorkingDirectory())
            model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
        else
            model->setFilter(QDir::AllEntries | QDir::NoDot);

        ui->treeViewProject->setRootIndex(model->setRootPath(filePath));
        ui->treeViewProject->setCurrentIndex(model->index(filePath));
        APP->getActiveProject()->setCurrentDirectory(filePath + QDir::separator());
        return;
    }
    emit fileSelected(filePath);

}

void ProjectWidget::filterFiles()
{
    QStringList filters;
    filters << "*" + ui->filterLineEdit->text() + "*";
    model->setNameFilters(filters);
    model->setNameFilterDisables(false);
    ui->treeViewProject->setModel(model);
}
