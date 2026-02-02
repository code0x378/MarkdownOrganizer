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

#include "projectdockwidget.h"
#include "ui_projectdockwidget.h"

#include <QFileSystemModel>
#include <QHeaderView>
#include <QMenu>
#include <QMessageBox>
#include <QTextStream>

#include "mdocore/mdoapplication.h"
#include "mdocore/logmanager.h"
#include "mdocore/util/qtutils.h"
#include "mdoapp/gui/appmainwindow.h"

ProjectDockWidget::ProjectDockWidget(QWidget *parent) :
    DsDockWidget(),
    ui(new Ui::ProjectDockWidget)
{
    ui->setupUi(this);
    ui->treeViewProject->setRootIsDecorated(false);
    ui->treeViewProject->setExpandsOnDoubleClick(true);
    ui->treeViewProject->setContextMenuPolicy(Qt::ActionsContextMenu);

    contextMenu = new QMenu(ui->treeViewProject);
    deleteAction = new QAction("Delete", contextMenu);
    VERIFY(connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteFile())));
    ui->treeViewProject->addAction(deleteAction);

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
    VERIFY(connect(ui->treeViewProject, SIGNAL(doubleClicked(const QModelIndex &)),
                   this,
                   SLOT(loadFile(const QModelIndex &))));
    VERIFY(connect(ui->treeViewProject, SIGNAL(pressed(const QModelIndex &)), this,
                   SLOT(selectFile(const QModelIndex &))));
    VERIFY(connect(ui->filterLineEdit, SIGNAL(textChanged(const QString &)), this,
                   SLOT(filterFiles())));
    VERIFY(connect(ui->treeViewProject,
                   SIGNAL(customContextMenuRequested(const QPoint &)),
                   this, SLOT(onCustomContextMenu(const QPoint &))));
    selectActiveProduct();
}

ProjectDockWidget::~ProjectDockWidget()
{
    delete ui;
}

void ProjectDockWidget::changeProject()
{
    QString projectName = ui->comboBoxProjects->currentText();
    APP->setActiveProject(APP->getProjects()->value(projectName));
    ui->treeViewProject->setRootIndex(model->setRootPath(
                                          APP->getActiveProject()->getWorkingDirectory()));
    APP->getActiveProject()->setCurrentDirectory(
        APP->getActiveProject()->getWorkingDirectory());
    model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    Q_EMIT projectChanged(projectName);
    LOG_INFO("Project changed:" + projectName);
}


void ProjectDockWidget::onCustomContextMenu(const QPoint &point)
{
    QModelIndex index = ui->treeViewProject->indexAt(point);
    if (index.isValid() && index.row() % 2 == 0) {
        contextMenu->exec(ui->treeViewProject->mapToGlobal(point));
    }
}

void ProjectDockWidget::selectActiveProduct()
{
    QString projectName = APP->getActiveProject()->getName();
    ui->treeViewProject->setRootIndex(model->setRootPath(
                                          APP->getActiveProject()->getWorkingDirectory()));;
    ui->comboBoxProjects->setCurrentIndex(ui->comboBoxProjects->findText(
                                              projectName));
    APP->getActiveProject()->setCurrentDirectory(
        APP->getActiveProject()->getWorkingDirectory());
    model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    Q_EMIT projectChanged(projectName);
}

void ProjectDockWidget::selectFile(const QModelIndex index)
{
    activeFilePath = new QString(model->fileInfo(index).absoluteFilePath()) ;
}

void ProjectDockWidget::loadFile(const QModelIndex index)
{
    QFileInfo fileInfo(*activeFilePath);
    if (fileInfo.isDir()) {
        if (*activeFilePath + QDir::separator() ==
                APP->getActiveProject()->getWorkingDirectory())
            model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
        else
            model->setFilter(QDir::AllEntries | QDir::NoDot);

        ui->treeViewProject->setRootIndex(model->setRootPath(*activeFilePath));
        ui->treeViewProject->setCurrentIndex(model->index(*activeFilePath));
        APP->getActiveProject()->setCurrentDirectory(*activeFilePath +
                                                     QDir::separator());
        return;
    }
    Q_EMIT fileSelected(*activeFilePath);

}

void ProjectDockWidget::deleteFile()
{

    QFileInfo fileInfo(*activeFilePath);
    if (fileInfo.isDir()) {
        QMessageBox::warning(this, "Delete Denied", "Directories are not supported");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm deletion", "Delete?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        LOG_INFO("Deleting file:" + *activeFilePath);
        QFile selectedFile (*activeFilePath);
        selectedFile.remove();
    } else {
        LOG_INFO("File deletion cancelled");
    }
    Q_EMIT fileDeleted(*activeFilePath);
}

void ProjectDockWidget::filterFiles()
{
    QStringList filters;
    filters << "*" + ui->filterLineEdit->text() + "*";
    model->setNameFilters(filters);
    model->setNameFilterDisables(false);
    ui->treeViewProject->setModel(model);
}
