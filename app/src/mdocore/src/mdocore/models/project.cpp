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

#include "project.h"

Project::Project()
{


}

QString Project::getName() const
{
    return name;
}

void Project::setName(const QString &value)
{
    name = value;
}

QString Project::getDescription() const
{
    return description;
}

void Project::setDescription(const QString &value)
{
    description = value;
}

QString Project::getWorkingDirectory() const
{
    return workingDirectory;
}

void Project::setWorkingDirectory(const QString &value)
{
    workingDirectory = value;
}

QString Project::getPostSaveCommmand() const
{
    return postSaveCommmand;
}

void Project::setPostSaveCommmand(const QString &value)
{
    postSaveCommmand = value;
}

ProjectType Project::getType() const
{
    return type;
}

void Project::setType(const ProjectType &value)
{
    type = value;
}

bool Project::getIsDefault() const
{
    return isDefault;
}

void Project::setIsDefault(bool value)
{
    isDefault = value;
}

QString Project::getTags() const
{
    return tags;
}

void Project::setTags(const QString &value)
{
    tags = value;
}

QString Project::getCategories() const
{
    return categories;
}

void Project::setCategories(const QString &value)
{
    categories = value;
}

QString Project::getCurrentDirectory() const
{
    return currentDirectory;
}

void Project::setCurrentDirectory(const QString &value)
{
    currentDirectory = value;
}

QString Project::getPlugins() const
{
    return plugins;
}

void Project::setPlugins(const QString &value)
{
    plugins = value;
}

QString Project::getEmailTo() const
{
    return emailTo;
}

void Project::setEmailTo(const QString &value)
{
    emailTo = value;
}

QString Project::getEmailFrom() const
{
    return emailFrom;
}

void Project::setEmailFrom(const QString &value)
{
    emailFrom = value;
}
