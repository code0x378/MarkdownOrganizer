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

#ifndef IPLUGIN
#define IPLUGIN

#include <QString>
#include <QMainWindow>
#include <QStringList>
#include <QDebug>

class MainWindow;
class PluginData;
class Project;
class Resource;

class IPlugin
{

public:
    virtual ~IPlugin() {}

    virtual bool initialize()
    {
        return true;
    }

    virtual bool save (const Project &project, const Resource &resource )
    {
        return true;
    }

    virtual bool finalize()
    {
        return true;
    }

    virtual QString getName() const = 0;
    virtual QString getCategory() const  = 0;
    virtual QString getVersion() const = 0;
    virtual QString getPublisher() const = 0;
    virtual QString getPublisherWebsite() const = 0;
    virtual QString getPublisherContact() const = 0;
    virtual QString getDescription() const = 0;
    virtual QString getCopyright() const = 0;
    virtual QString getLicense() const = 0;

public:
    PluginData *data;
};

Q_DECLARE_INTERFACE(IPlugin, "com.thoughtlogix.IPlugin")

#endif // IPLUGIN
