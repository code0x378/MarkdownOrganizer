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

#include "projectdialog.h"
#include "ui_projectdialog.h"

#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>
#include <QMessageBox>
#include <QCheckBox>
#include <QItemSelectionModel>
#include <QHeaderView>

#include <mdocore/models/project.h>
#include <mdocore/util/qtutils.h>
#include <mdocore/logmanager.h>\
#include <mdocore/mdoapplication.h>
#include <mdocore/pluginmanager.h>
#include <mdocore/mdoapplication.h>

ProjectDialog::ProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectDialog)
{
    ui->setupUi(this);
    loadProjects();
    displayPlugins();

    QList<QString> types;
    types.append("Generic");
    types.append("Blog");
    types.append("Bookmarks");
    types.append("Help System");
    types.append("Notes");
    ui->projectComboBox->addItems(types);

    VERIFY(connect(ui->savePushButton, SIGNAL(released()), this,
                   SLOT(addProject())));
    VERIFY(connect(ui->newToolButton, SIGNAL(released()), this,
                   SLOT(newProject())));
    VERIFY(connect(ui->deleteToolButton, SIGNAL(released()), this,
                   SLOT(deleteProject())));
    LOG_DEBUG("Project dialog loaded");
}

ProjectDialog::~ProjectDialog()
{
    delete ui;
}

void ProjectDialog::displayPlugins()
{
    QList<QCheckBox *> checkboxes = ui->pluginGroupBox->findChildren<QCheckBox *>();
    for (QCheckBox *chk : checkboxes)
        delete chk;

    int row = 1;
    int col = 1;
    QStringList projectPlugins = APP->getActiveProject()->getTags().split(",");
    QGridLayout *layout = new QGridLayout();
    delete ui->pluginGroupBox->layout();
    ui->pluginGroupBox->setLayout (layout);

    foreach (IPlugin *plugin, PLUGIN_MANAGER->getPluginList()) {
        QCheckBox *chk = new QCheckBox(plugin->getName());
        connect(chk, SIGNAL(clicked()), this, SLOT(onToggled()));
        layout->addWidget(chk, row - 1, col - 1, 1, 1);

        if (col % 3 == 0) {
            col = 1;
            row++;
        } else {
            col++;
        }
    }
}

QString ProjectDialog::getSelectedPlugins()
{
    QString plugins;
    QList<QCheckBox *> checkboxes = ui->pluginGroupBox->findChildren<QCheckBox *>();
    for (QCheckBox *chk : checkboxes)
        if(chk->isChecked())
            plugins += chk->text() + ", ";

    return plugins;
}


void ProjectDialog::addProject()
{
    selectedProject = new Project();
    selectedProject->setName(ui->nameLineEdit->text());
    selectedProject->setDescription(ui->descriptionLineEdit->text());
    selectedProject->setTags(ui->tagsLineEdit->text());
    selectedProject->setWorkingDirectory(ui->workingDirLineEdit->text());
    selectedProject->setPostSaveCommmand(ui->posttSaveCommmandLineEdit->text());
    selectedProject->setEmailTo(ui->toLineEdit->text());
    selectedProject->setEmailFrom(ui->fromLineEdit->text());
    selectedProject->setCategories(ui->categoriesLineEdit->text());
    selectedProject->setIsDefault(ui->isDefaultCheckBox->checkState());
    selectedProject->setType(ui->projectComboBox->currentIndex());
    selectedProject->setPlugins(getSelectedPlugins());

    Project::saveProject(selectedProject);
}

void ProjectDialog::deleteProject()
{
    int idx = ui->projectTableView->currentIndex().row();
    selectedProject = model->getProjects().at(idx);
    Project::deleteProject(selectedProject);
    model->removeRow(idx);
}

void ProjectDialog::onToggled()
{
    model->getProjects().at(ui->projectTableView->currentIndex().row())->setPlugins(getSelectedPlugins());

}

void ProjectDialog::newProject()
{
    ui->nameLineEdit->setText("");
    ui->descriptionLineEdit->setText("");
    ui->workingDirLineEdit->setText("");
    ui->posttSaveCommmandLineEdit->setText("");
    ui->toLineEdit->setText("");
    ui->fromLineEdit->setText("");
    ui->tagsLineEdit->setText("");
    ui->categoriesLineEdit->setText("");
    ui->projectComboBox->setCurrentText("Blog");
    ui->isDefaultCheckBox->setCheckState(Qt::CheckState::Checked);
}

void ProjectDialog::loadProjects()
{

    model = new ProjectTableModel(APP->getProjects()->values(), ui->projectTableView);

    ui->projectTableView->setModel(model);
    ui->projectTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->projectTableView->setModel(model);
    ui->projectTableView->horizontalHeader()->setStretchLastSection(true);
    ui->projectTableView->verticalHeader()->hide();
    ui->projectTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->projectTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->projectTableView->setSortingEnabled(true);

    connect(ui->projectTableView->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
            this, SLOT(editSelectedProject(QModelIndex)));

    connect(ui->projectTableView->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
            this, SLOT(updateSelectedTabs(QModelIndex)));
}


void ProjectDialog::editSelectedProject(const QModelIndex &index)
{
     auto projects = model->getProjects();

         int i = ui->projectTableView->currentIndex().row();

         if(i < 0) {
             return;
         }

         selectedProject = projects.at(i);

         ui->nameLineEdit->setText(selectedProject->getName());
         ui->descriptionLineEdit->setText(selectedProject->getDescription());
         ui->workingDirLineEdit->setText(selectedProject->getWorkingDirectory());
         ui->posttSaveCommmandLineEdit->setText(selectedProject->getPostSaveCommmand());
         ui->toLineEdit->setText(selectedProject->getEmailTo());
         ui->fromLineEdit->setText(selectedProject->getEmailFrom());
         ui->tagsLineEdit->setText(selectedProject->getTags());
         ui->categoriesLineEdit->setText(selectedProject->getCategories());
         ui->projectComboBox->setCurrentIndex(selectedProject->getType());
         ui->isDefaultCheckBox->setCheckState((Qt::CheckState) selectedProject->getIsDefault());

         updateSelectedTabs(ui->projectTableView->currentIndex());

}

void ProjectDialog::updateSelectedTabs(const QModelIndex &index)
{
    QString plugins = model->getProjects().at(ui->projectTableView->currentIndex().row())->getPlugins();

    QList<QCheckBox *> checkboxes = ui->pluginGroupBox->findChildren<QCheckBox *>();

    for (QCheckBox *chk : checkboxes) {
        chk->setChecked(false);
    }

    for (QCheckBox *chk : checkboxes) {
        for (QString pluginName : plugins.split(",")) {
            if (chk->text() == pluginName.trimmed())
                chk->setChecked(true);
        }
    }

}


