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


#ifndef HUGOPUGIN_H
#define HUGOPUGIN_H

#include <QtPlugin>
#include <QObject>
#include "mdocore/iplugin.h"

class Project;
class Resource;

class HugoPlugin : public QObject, public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.JeffSmithDev.HugoPlugin")
    Q_INTERFACES(IPlugin)

public:

    bool initialize(const QStringList &arguments, QStringList *error_strings);
    bool save(const Project &project, const Resource &resource);
    bool finalize();
    QString getName() const;
    QString getCategory() const;
    QString getVersion() const;
    QString getPublisher() const;
    QString getPublisherWebsite() const;
    QString getPublisherContact() const;
    QString getDescription() const;
    QString getCopyright() const;
    QString getLicense() const;

};

#endif // HUGOPUGIN_H
