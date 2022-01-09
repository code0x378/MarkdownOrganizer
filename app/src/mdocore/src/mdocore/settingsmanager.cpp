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

#include "settingsmanager.h"

#include <QSettings>
#include <QDir>
#include <QCoreApplication>
#include <QMutex>
#include "global.h"
#include "mdoapplication.h"
#include "mdocore/logmanager.h"

SettingsManager::SettingsManager()
{
    settings = new QSettings(*APP->getSettingsFile(), QSettings::IniFormat);
}

SettingsManager *SettingsManager::settingsManager = nullptr;
SettingsManager *SettingsManager::instance()
{
    static QMutex mutex;
    if (!settingsManager) {
        mutex.lock();

        if (!settingsManager)
            settingsManager = new SettingsManager();

        mutex.unlock();
    }

    return settingsManager;
}


void SettingsManager::loadSettings()
{
    settings->sync();
    LOG_DEBUG("Settings loaded");
}

void SettingsManager::saveSettings()
{
    settings->sync();
    LOG_DEBUG("Settings saved");
}

void SettingsManager::init()
{

}

void SettingsManager::setSetting(const QString &key, const QVariant &variant)
{
    settings->setValue(key, variant);
}

void SettingsManager::setPassword(const QString &key,
                                  const QVariant &variant)
{
    QByteArray byteArray = variant.toString().toUtf8();
    char *ePtr = byteArray.data();

    for (int i = 0; ePtr[i] != '\0'; ++i)
        ePtr[i] += i;

    settings->setValue(key, QString::fromUtf8(ePtr));
}

QSettings *SettingsManager::getSettings() const
{
    return settings;
}

QVariant SettingsManager::getSetting(const QString &key,
                                     const QVariant &defaultValue)
{
    return settings->value(key, defaultValue);
}

QString SettingsManager::getString(const QString &key,
                                   const QString &defaultValue)
{
    return settings->value(key, defaultValue).toString();
}

bool SettingsManager::getBool(const QString &key, const bool &defaultValue)
{
    return settings->value(key, defaultValue).toBool();
}

int SettingsManager::getInt(const QString &key, const int &defaultValue)
{
    return settings->value(key, defaultValue).toInt();
}

QString SettingsManager::getPassword(const QString &key)
{
    QByteArray byteArray = settings->value(key).toString().toUtf8();
    char *ePtr = byteArray.data();
    for ( int i = 0; ePtr[i] != '\0'; ++i ) (ePtr[i] -= i);
    return QString::fromUtf8(ePtr);
}
