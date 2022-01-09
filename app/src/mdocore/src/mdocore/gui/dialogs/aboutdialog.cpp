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

#include "aboutdialog.h"

#include <QSysInfo>
#include "plugindialog.h"
#include "mdocore/pluginmanager.h"
#include "ui_aboutdialog.h"
#include "mdocore/logmanager.h"
#include "mdocore/mdoapplication.h"
#include "mdocore/settingsmanager.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    // Setup plugin information
    ui->pluginsTableWidget->setRowCount(PLUGIN_MANAGER->getPluginList().size());
    ui->pluginsTableWidget->setColumnCount(4);
    ui->pluginsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->pluginsTableWidget->setHorizontalHeaderLabels(
        QString("Name|Version|Type|Description").split("|"));

    for (int i = 0; i < PLUGIN_MANAGER->getPluginList().size(); i++) {
        ui->pluginsTableWidget->setItem(i, 0,
                                        new QTableWidgetItem(PLUGIN_MANAGER->getPluginList().at(i)->getName()));
        ui->pluginsTableWidget->setItem(i, 1,
                                        new QTableWidgetItem(PLUGIN_MANAGER->getPluginList().at(i)->getVersion()));
        ui->pluginsTableWidget->setItem(i, 2,
                                        new QTableWidgetItem(PLUGIN_MANAGER->getPluginList().at(i)->getCategory()));
        ui->pluginsTableWidget->setItem(i, 3,
                                        new QTableWidgetItem(PLUGIN_MANAGER->getPluginList().at(i)->getDescription()));
    }

    // Setup system information (.e. versions, env, etc)
    ui->systemInfoTableWidget->setRowCount(5);
    ui->systemInfoTableWidget->setColumnCount(2);
    ui->systemInfoTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->systemInfoTableWidget->setHorizontalHeaderLabels(
        QString("Property|Value").split("|"));
    ui->systemInfoTableWidget->setItem(0, 0, new QTableWidgetItem(tr("LibVer")));
    ui->systemInfoTableWidget->setItem(0, 1, new QTableWidgetItem(QT_VERSION_STR));
    ui->systemInfoTableWidget->setItem(1, 0, new QTableWidgetItem(tr("hostname")));
    ui->systemInfoTableWidget->setItem(1, 1,
                                       new QTableWidgetItem(QSysInfo::machineHostName()));
    ui->systemInfoTableWidget->setItem(2, 0,
                                       new QTableWidgetItem(tr("settingsDir")));
    ui->systemInfoTableWidget->setItem(2, 1,
                                       new QTableWidgetItem(*APP->getConfigDirectory()));
    ui->systemInfoTableWidget->setItem(3, 0,
                                       new QTableWidgetItem(tr("settingsFile")));
    ui->systemInfoTableWidget->setItem(3, 1,
                                       new QTableWidgetItem(*APP->getSettingsFile()));
    ui->systemInfoTableWidget->setItem(4, 0, new QTableWidgetItem(tr("logFile")));
    ui->systemInfoTableWidget->setItem(4, 1,
                                       new QTableWidgetItem(*APP->getLogFile()));

    //Load log file
    QFile file("log.txt");
    if (file.open(QIODevice::ReadWrite )) {
        ui->logPlainTextEdit->setPlainText(file.readAll());
    }

    LOG_DEBUG("About dialog loaded");
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

