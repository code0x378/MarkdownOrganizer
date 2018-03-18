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

#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QString>
#include <QVariant>
#include <QSettings>

#include "mdocore/global.h"

class SettingsManager
{
public:
    SettingsManager();
    static SettingsManager *instance();

    void loadSettings();
    void saveSettings();
    void setSetting(const QString &key, const QVariant &variant = QVariant());
    QString getString(const QString &key, const QString &defaultValue = QString());
    bool getBool(const QString &key, const bool &defaultValue  = false);
    int getInt(const QString &key, const int &defaultValue = 0 );
    QString getPassword(const QString &key);
    void setPassword(const QString &key, const QVariant &variant);

    QSettings *getSettings() const;

    QVariant getSetting(const QString &key, const QVariant &defaultValue);
private:
    static SettingsManager *settingsManager;
    QSettings *settings;
    void init();
};

#define SETTINGS_MANAGER SettingsManager::instance()
#define SETTINGS_MANAGER_INITIALIZE SettingsManager::instance()

#endif // SETTINGSMANAGER_H
