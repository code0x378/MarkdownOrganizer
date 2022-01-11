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

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include "mdocore/logmanager.h"
#include "mdocore/settingsmanager.h"
#include "mdocore/util/qtutils.h"

#include <QMessageBox>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->menuTreeWidget->setColumnCount(1);
    ui->menuTreeWidget->setHeaderLabel("Categories");
    ui->menuTreeWidget->setRootIsDecorated(false);
    QList<QTreeWidgetItem *> items;
    items.append(new QTreeWidgetItem((QTreeWidget *)0, QStringList("General")));
    items.append(new QTreeWidgetItem((QTreeWidget *)0,
                                     QStringList("User Interface")));
    items.append(new QTreeWidgetItem((QTreeWidget *)0, QStringList("Email")));
    ui->menuTreeWidget->insertTopLevelItems(0, items);
    connect(ui->menuTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this,
            SLOT(handleTreeMenuSelection(QTreeWidgetItem *, int)));

    loadDefaults();
    loadSettings();

    VERIFY(connect(ui->themeComboBox, SIGNAL(currentIndexChanged(QString)), this,
                   SLOT(notifyToRestart())));

    LOG_DEBUG("Settings dialog loaded");
}

void SettingsDialog::handleTreeMenuSelection(QTreeWidgetItem *item, int idx)
{
    QString itemText = item->text(0);
    if (itemText == "General") {
        ui->stackedWidget->setCurrentIndex(0);
    } else if (itemText == "User Interface") {
        ui->stackedWidget->setCurrentIndex(1);
    } else if (itemText == "Email") {
        ui->stackedWidget->setCurrentIndex(2);
    }
}

void SettingsDialog::notifyToRestart() {
    restartRequired = true;
}

void SettingsDialog::accept()
{
    SETTINGS_MANAGER->setSetting("Interface/Theme",
                                 ui->themeComboBox->currentText());
    SETTINGS_MANAGER->setSetting("Interface/ColorScheme",
                                 ui->colorSchemeComboBox->currentText());

    SETTINGS_MANAGER->setSetting("Email/Server",
                                 ui->emailServerLineEdit->text());
    SETTINGS_MANAGER->setSetting("Email/User",
                                 ui->emailUserLineEdit->text());
    SETTINGS_MANAGER->setSetting("Email/Password",
                                 ui->emailPasswordLineEdit->text());
    SETTINGS_MANAGER->setSetting("Email/Port",
                                 ui->emailPortLineEdit->text());

    SETTINGS_MANAGER->saveSettings();

    if(restartRequired) {
        QMessageBox::information(this, tr("Restart Required"), tr("Please restart for the changes to take effect."));
    }
    close();
}

void SettingsDialog::loadDefaults()
{
    QStringList colorSchemes;
    colorSchemes  << "Simple" << "Dark" << "Dracula1" << "Dracula2" << "Intellij";
    ui->colorSchemeComboBox->addItems(colorSchemes);

    QStringList themes;
    themes  << "Native" << "Fusion" << "Fusion - Dark";
    ui->themeComboBox->addItems(themes);
}

void  SettingsDialog::loadSettings()
{
    ui->themeComboBox->setCurrentText(
                SETTINGS_MANAGER->getString("Interface/Theme", "Fusion"));
    ui->colorSchemeComboBox->setCurrentText(
                SETTINGS_MANAGER->getString("Interface/ColorScheme", "Dark"));

    ui->emailServerLineEdit->setText(
                SETTINGS_MANAGER->getString("Email/Server", ""));

    ui->emailUserLineEdit->setText(
                SETTINGS_MANAGER->getString("Email/User", ""));

    ui->emailPasswordLineEdit->setText(
                SETTINGS_MANAGER->getString("Email/Password", ""));

    ui->emailPortLineEdit->setText(
                SETTINGS_MANAGER->getString("Email/Port", ""));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
