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


#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "mdocore/iplugin.h"

class PluginManager
{
public:
    PluginManager();
    ~PluginManager();
    static PluginManager *instance();
    void loadPlugins();

    QList<IPlugin *> getPluginList() const;
    void setPluginList(const QList<IPlugin *> &value);
    IPlugin *getActivePlugin();

private :
    QList<IPlugin *> pluginList;
    static PluginManager *pluginManager;
};


#define PLUGIN_MANAGER PluginManager::instance()
#define PLUGIN_MANAGER_INITIALIZE PluginManager::instance()

#endif // PLUGINMANAGER_H
