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


#include "coreplugin.h"
#include "mdocore/global.h"
#include "mdocore/plugindata.h"

bool CorePlugin::initialize(const QStringList &arguments,
                            QStringList *error_strings)
{
    Q_UNUSED(arguments);
    Q_UNUSED(error_strings);
    data = new PluginData();
    return true;
}

bool CorePlugin::save(const Project &project, const Resource &resource)
{
    return true;
}

bool CorePlugin::finalize()
{
    return true;
}

QString CorePlugin::getName() const
{
    return "Core";
}
QString CorePlugin::getCategory() const
{
    return "General";
}
QString CorePlugin::getVersion() const
{
    return "1.5.0";
}
QString CorePlugin::getPublisher() const
{
    return "ThoughtLogix";
}
QString CorePlugin::getPublisherWebsite() const
{
    return "http://www.thoughtlogix.com";
}
QString CorePlugin::getPublisherContact() const
{
    return "support@thoughtlogix.com";
}
QString CorePlugin::getDescription() const
{
    return tr("Common plugin functionality");
}
QString CorePlugin::getCopyright() const
{
    return QString(tr("Copyright") + " 2018 ThoughtLogix.");
}
QString CorePlugin::getLicense() const
{
    return tr("See the MarkdownOrganizer Plugin License");
}
