/*
* Markdown Organizer
* Copyright (C) 2016-2018 JeffSmithDev
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

#include "pluginmanager.h"

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QMutex>
#include <QPluginLoader>

#include "mdocore/logmanager.h"
#include "mdocore/slugify.hpp"

PluginManager::PluginManager()
{
}

PluginManager::~PluginManager()
{

}

PluginManager *PluginManager::pluginManager = 0;
PluginManager *PluginManager::instance()
{
    static QMutex mutex;
    if (!pluginManager) {
        mutex.lock();

        if (!pluginManager)
            pluginManager = new PluginManager();

        mutex.unlock();
    }

    return pluginManager;
}

void PluginManager::loadPlugins()
{

    QDir pluginsDir = QDir(qApp->applicationDirPath());

#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug"
            || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    pluginsDir.cd("plugins");

    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin != NULL) {
            IPlugin *currentPlugin = qobject_cast<IPlugin *>(plugin);
            qDebug() << "Loading Plugin:" << currentPlugin->getName();
            pluginList.append(currentPlugin);
            currentPlugin->initialize();
        } else {
            qWarning() << "Error loading plugin: " << loader.errorString();
        }
    }
}

QList<IPlugin *> PluginManager::getPluginList() const
{
    return pluginList;
}

void PluginManager::setPluginList(const QList<IPlugin *> &value)
{
    pluginList = value;
}

IPlugin *PluginManager::getActivePlugin()
{
    foreach (IPlugin *plugin,  pluginList) {
        if (plugin->getName() == "Hugo") {
            return plugin;
        }
    }

    return nullptr;
}

