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


#include "mdoplugin.h"

#include <QWidget>
#include <QApplication>
#include "mdocore/global.h"
#include "mdocore/plugindata.h"

bool MdoPlugin::initialize(const QStringList &arguments,
                           QStringList *error_strings)
{
    Q_UNUSED(arguments);
    Q_UNUSED(error_strings);
    data = new PluginData();
    return true;
}

bool MdoPlugin::save(const Project &project, const Resource &resource)
{
    return true;
}

bool MdoPlugin::finalize()
{
    return true;
}

QString MdoPlugin::getName() const
{
    return "Mdo";
}
QString MdoPlugin::getCategory() const
{
    return "Web";
}
QString MdoPlugin::getVersion() const
{
    return "1.0.0";
}
QString MdoPlugin::getPublisher() const
{
    return "JeffSmithDev";
}
QString MdoPlugin::getPublisherWebsite() const
{
    return "http://www.JeffSmithDev.com";
}
QString MdoPlugin::getPublisherContact() const
{
    return "support@JeffSmithDev.com";
}
QString MdoPlugin::getDescription() const
{
    return tr("A plugin to save content to markdownorganizer.com");
}
QString MdoPlugin::getCopyright() const
{
    return QString(tr("Copyright") + " 2017 JeffSmithDev.");
}
QString MdoPlugin::getLicense() const
{
    return tr("See the MarkdownOrganizer Plugin License");
}
