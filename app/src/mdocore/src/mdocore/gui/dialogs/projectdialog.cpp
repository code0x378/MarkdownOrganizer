/*
* Markdown Organizer
* Copyright (C) 2016-2018 LittleDogBigUniverse
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
#include <mdocore/logmanager.h>
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


void ProjectDialog::addProject()
{
    QString plugins;
    QList<QCheckBox *> checkboxes = ui->pluginGroupBox->findChildren<QCheckBox *>();
    for (QCheckBox *chk : checkboxes)
        plugins += chk->text() + ", ";

    QSqlRecord rec;
    rec.append(QSqlField("name", QVariant::String));
    rec.append(QSqlField("description", QVariant::String));
    rec.append(QSqlField("workingDirectory", QVariant::String));
    rec.append(QSqlField("postSaveCommand", QVariant::String));
    rec.append(QSqlField("tags", QVariant::String));
    rec.append(QSqlField("categories", QVariant::String));
    rec.append(QSqlField("projectType", QVariant::Int));
    rec.append(QSqlField("isDefault", QVariant::Bool));
    rec.append(QSqlField("plugins", QVariant::String));
    rec.setValue("name", ui->nameLineEdit->text());
    rec.setValue("description", ui->descriptionLineEdit->text());
    rec.setValue("workingDirectory", ui->workingDirLineEdit->text());
    rec.setValue("postSaveCommand", ui->posttSaveCommmandLineEdit->text());
    rec.setValue("tags", ui->tagsLineEdit->text());
    rec.setValue("catregories", ui->categoriesLineEdit->text());
    rec.setValue("projectType", ui->projectComboBox->currentIndex() + 1);
    rec.setValue("isDefault", ui->isDefaultCheckBox->checkState());
    rec.setValue("plugins", plugins);
    model->insertRecord(-1, rec);
    if (model->lastError().text() != "")
        LOG_INFO(model->lastError().text());
}

void ProjectDialog::deleteProject()
{
    model->removeRow(ui->projectTableView->currentIndex().row());
    model->select();
}

void ProjectDialog::onToggled()
{
    QString plugins;
    QList<QCheckBox *> checkboxes = ui->pluginGroupBox->findChildren<QCheckBox *>();
    for (QCheckBox *chk : checkboxes)
        plugins += chk->text() + ", ";

    model-> record(ui->projectTableView->currentIndex().row()).setValue("plugins",
                                                                        plugins);
    model->submitAll();
}

void ProjectDialog::newProject()
{
    // todo: fix this hack and clear selected properly
    model->select();
    ui->nameLineEdit->setText("");
    ui->descriptionLineEdit->setText("");
    ui->workingDirLineEdit->setText("");
    ui->posttSaveCommmandLineEdit->setText("");
    ui->toLineEdit->setText("");
    ui->fromLineEdit->setText("");
}

void ProjectDialog::loadProjects()
{
    model = new QSqlRelationalTableModel(ui->projectTableView);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setTable("projects");

    int projectTypeIdx = model->fieldIndex("projectType");

    model->setRelation(projectTypeIdx, QSqlRelation("project_types", "id", "name"));
    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, tr("name"));
    model->setHeaderData(model->fieldIndex("workingDirectory"), Qt::Horizontal,
                         tr("workingDirectory"));
    model->setHeaderData(model->fieldIndex("postSaveCommand"), Qt::Horizontal,
                         tr("postSaveCommand"));
    model->setHeaderData(model->fieldIndex("tags"), Qt::Horizontal,
                         tr("tags"));
    model->setHeaderData(model->fieldIndex("categories"), Qt::Horizontal,
                         tr("categories"));
    model->setHeaderData(projectTypeIdx, Qt::Horizontal, tr("ProjectType"));

    if (!model->select()) {
        QMessageBox::critical(this, "Unable to load projects",
                              "Unable to load projects");
        return;
    }

    ui->projectTableView->setModel(model);
    ui->projectTableView->setColumnHidden(model->fieldIndex("id"), true);
    ui->projectTableView->setColumnHidden(model->fieldIndex("workingDirectory"),
                                          true);
    ui->projectTableView->setColumnHidden(model->fieldIndex("postSaveCommand"),
                                          true);
    ui->projectTableView->setColumnHidden(model->fieldIndex("tags"),
                                          true);
    ui->projectTableView->setColumnHidden(model->fieldIndex("categories"),
                                          true);
    ui->projectTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->projectTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
//    ui->projectTableView->horizontalHeader()->setSectionResizeMode(
//        QHeaderView::Stretch);

    ui->projectComboBox->setModel(model->relationModel(projectTypeIdx));
    ui->projectComboBox->setModelColumn(model->relationModel(
                                            projectTypeIdx)->fieldIndex("name"));

    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->addMapping(ui->nameLineEdit, model->fieldIndex("name"));
    mapper->addMapping(ui->descriptionLineEdit, model->fieldIndex("description"));
    mapper->addMapping(ui->workingDirLineEdit,
                       model->fieldIndex("workingDirectory"));
    mapper->addMapping(ui->posttSaveCommmandLineEdit,
                       model->fieldIndex("postSaveCommand"));
    mapper->addMapping(ui->tagsLineEdit,
                       model->fieldIndex("tags"));
    mapper->addMapping(ui->categoriesLineEdit,
                       model->fieldIndex("categories"));
    mapper->addMapping(ui->projectComboBox, projectTypeIdx);
    mapper->addMapping(ui->isDefaultCheckBox, model->fieldIndex("isDefault"));
    mapper->addMapping(ui->toLineEdit, model->fieldIndex("emailTo"));
    mapper->addMapping(ui->fromLineEdit, model->fieldIndex("emailFrom"));

    connect(ui->projectTableView->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
            mapper, SLOT(setCurrentModelIndex(QModelIndex)));

    connect(ui->projectTableView->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
            this, SLOT(updateSelectedTabs(QModelIndex)));
    //    ui->projectTableView->setCurrentIndex(model->index(0, 0));
}

void ProjectDialog::updateSelectedTabs(const QModelIndex &index)
{
    QString plugins = model-> record(index.row()).value("plugins").toString();

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
